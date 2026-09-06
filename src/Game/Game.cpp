#include "Game/Game.hpp"

#include "PieceType.hpp"

Game::Game()
    : white_player_(Color::White),
      black_player_(Color::Black),
      current_player_color_(Color::White),
      result_(GameResult::InProgress),
      command_handler_(board_, white_player_, black_player_,
                       current_player_color_, result_, view_, renderer_,
                       move_validator_, move_parser_, input_reader_,
                       input_normalizer_, move_history_) {}

void Game::run() {
  view_.printWelcomeMessage();

  if (!handleMainMenu()) {
    return;
  }

  setupGame();
  while (result_ == GameResult::InProgress) {
    handleTurn();
  }
  view_.printResult(result_, getCurrentPlayer());
}

bool Game::handleMainMenu() {
  while (true) {
    view_.printMainMenu();

    std::string input = input_normalizer_.normalize(input_reader_.readLine());

    if (input == "start") {
      view_.printGameStartMessage();
      return true;
    }

    if (input == "rules") {
      view_.printRules();
      continue;
    }

    if (input == "help") {
      view_.printHelp();
      continue;
    }

    if (input == "quit") {
      view_.printGoodbye();
      return false;
    }

    view_.printInvalidCommand();
  }
}

void Game::setupGame() {
  result_ = GameResult::InProgress;
  current_player_color_ = Color::White;
  setup_.setupPieces(board_, white_player_, black_player_);
  renderer_.printBoard(board_, white_player_);
}

void Game::handleTurn() {
  while (true) {
    view_.printTurnPrompt(current_player_color_);
    std::string input = input_normalizer_.normalize(input_reader_.readLine());

    const CommandResult command_result = command_handler_.handleCommand(input);
    if (command_result == CommandResult::GameEnded) {
      return;
    }
    if (command_result == CommandResult::Handled) {
      continue;
    }

    if (processMoveInput(input)) {
      return;
    }
  }
}

bool Game::processMoveInput(const std::string &input) {
  std::optional<Move> move = move_parser_.parseMove(input);
  if (!move.has_value()) {
    return handleInvalidInput();
  }

  const std::optional<MoveRecord> last_record = move_history_.getLastRecord();
  if (!move_validator_.isValidMove(board_, move.value(), current_player_color_,
                                   last_record)) {
    return handleInvalidMove();
  }

  const Move &valid_move = move.value();
  const Piece *moving_piece = board_.getPiece(valid_move.getFrom());
  if (moving_piece == nullptr) {
    return handleInvalidMove();
  }

  const Color moving_player_color = current_player_color_;
  const PieceType moving_piece_type = moving_piece->getPieceType();

  const Piece *captured_piece = board_.getPiece(valid_move.getTo());
  if (captured_piece == nullptr &&
      move_validator_.isEnPassantMove(board_, valid_move, current_player_color_,
                                      last_record)) {
    captured_piece = board_.getPiece(last_record.value().getTo());
  }

  std::optional<PieceType> captured_piece_type = std::nullopt;
  if (captured_piece != nullptr) {
    captured_piece_type = captured_piece->getPieceType();
  }

  const std::optional<PieceType> promoted_piece_type = executeMove(valid_move);

  MoveRecord record(moving_player_color, valid_move.getFrom(),
                    valid_move.getTo(), moving_piece_type, captured_piece_type,
                    promoted_piece_type);

  move_history_.addRecord(record);
  finishTurnAfterMove();

  return true;
}

bool Game::isGameOver() const { return result_ != GameResult::InProgress; }

std::optional<PieceType> Game::executeMove(const Move &move) {
  std::optional<PieceType> promoted_piece_type = std::nullopt;

  if (move_validator_.isCastlingMove(board_, move, current_player_color_)) {
    executeCastling(move);
  } else {
    handleCapture(move);
    handleEnPassantCapture(move);
    board_.movePiece(move);

    promoted_piece_type = handlePromotion(move);
  }

  switchPlayer();
  return promoted_piece_type;
}

void Game::executeCastling(const Move &move) {
  Coordinate king_from = move.getFrom();
  Coordinate king_to = move.getTo();

  int column_difference = static_cast<int>(king_to.getColumn()) -
                          static_cast<int>(king_from.getColumn());

  std::size_t rook_from_column = 0;
  std::size_t rook_to_column = 0;

  if (column_difference > 0) {
    rook_from_column = 7;
    rook_to_column = 5;
  } else {
    rook_from_column = 0;
    rook_to_column = 3;
  }

  Coordinate rook_from(king_from.getRow(), rook_from_column);
  Coordinate rook_to(king_from.getRow(), rook_to_column);

  Move rook_move(rook_from, rook_to);

  board_.movePiece(move);
  board_.movePiece(rook_move);
}

void Game::finishTurnAfterMove() {
  std::optional<Coordinate> checked_king =
      move_validator_.getCheckedKingCoordinate(board_, current_player_color_);

  renderer_.printBoard(board_, getCurrentPlayer(), checked_king);

  if (move_validator_.isCheckmate(board_, current_player_color_)) {
    printCheckStatus();
    view_.printCheckmate();
    setOpponentAsWinner();
    return;
  }

  if (move_validator_.isStalemate(board_, current_player_color_)) {
    view_.printStalemate();
    result_ = GameResult::Draw;
    return;
  }

  if (checked_king.has_value()) {
    printCheckStatus();
  }
}

void Game::handleCapture(const Move &move) {
  const Piece *target_piece = board_.getPiece(move.getTo());
  if (target_piece == nullptr) {
    return;
  }

  if (target_piece->getPieceColor() == current_player_color_) {
    return;
  }

  const PieceType piece_type = target_piece->getPieceType();
  const int piece_value = target_piece->getValue();
  if (current_player_color_ == Color::White) {
    white_player_.addCapturedPiece(piece_type);
    white_player_.setScore(white_player_.getScore() + piece_value);
  } else {
    black_player_.addCapturedPiece(piece_type);
    black_player_.setScore(black_player_.getScore() + piece_value);
  }

  board_.removePiece(move.getTo());
}

void Game::handleEnPassantCapture(const Move &move) {
  const std::optional<MoveRecord> last_record = move_history_.getLastRecord();
  if (!move_validator_.isEnPassantMove(board_, move, current_player_color_,
                                       last_record)) {
    return;
  }

  const Coordinate captured_coordinate = last_record.value().getTo();
  const Piece *captured_piece = board_.getPiece(captured_coordinate);
  if (captured_piece == nullptr) {
    return;
  }

  const PieceType piece_type = captured_piece->getPieceType();
  const int piece_value = captured_piece->getValue();

  Player &player = getPlayerByColor(current_player_color_);
  player.addCapturedPiece(piece_type);
  player.setScore(player.getScore() + piece_value);

  board_.removePiece(captured_coordinate);
}

std::optional<PieceType> Game::handlePromotion(const Move &move) {
  Coordinate to = move.getTo();
  const Piece *piece = board_.getPiece(to);
  if (!canPromote(piece, to)) {
    return std::nullopt;
  }

  Player &player = getPlayerByColor(piece->getPieceColor());
  std::unique_ptr<Piece> new_piece =
      createPromotionPiece(piece->getPieceColor());

  const std::string promoted_piece_name =
      pieceTypeToString(new_piece->getPieceType());

  Piece *promoted_piece = player.promotePiece(piece, std::move(new_piece));

  if (promoted_piece != nullptr) {
    board_.setPiece(to, promoted_piece);
    view_.printPromotionResult(player, promoted_piece_name);
    return promoted_piece->getPieceType();
  }
  return std::nullopt;
}

std::unique_ptr<Piece> Game::createPromotionPiece(Color color) {
  while (true) {
    view_.printPromotionMenu();

    std::string input = input_normalizer_.normalize(input_reader_.readLine());
    if (input == "queen" || input == "q") {
      return std::make_unique<Queen>(color);
    } else if (input == "rook" || input == "r") {
      return std::make_unique<Rook>(color);
    } else if (input == "bishop" || input == "b") {
      return std::make_unique<Bishop>(color);
    } else if (input == "knight" || input == "n") {
      return std::make_unique<Knight>(color);
    }
    view_.printInvalidPromotionChoice();
  }
}

bool Game::canPromote(const Piece *piece, const Coordinate &coordinate) const {
  if (piece == nullptr || piece->getPieceType() != PieceType::Pawn) {
    return false;
  }

  if (piece->getPieceColor() == Color::White) {
    return coordinate.getRow() == 0;
  }

  if (piece->getPieceColor() == Color::Black) {
    return coordinate.getRow() == 7;
  }

  return false;
}

void Game::switchPlayer() {
  current_player_color_ =
      current_player_color_ == Color::White ? Color::Black : Color::White;
}

void Game::setOpponentAsWinner() {
  result_ = current_player_color_ == Color::White ? GameResult::BlackWon
                                                  : GameResult::WhiteWon;
}

Player &Game::getPlayerByColor(Color color) {
  return color == Color::White ? white_player_ : black_player_;
}

const Player &Game::getCurrentPlayer() const {
  return current_player_color_ == Color::White ? white_player_ : black_player_;
}

bool Game::handleInvalidInput() const {
  view_.printInvalidInput();
  return false;
}

bool Game::handleInvalidMove() const {
  if (move_validator_.getCheckedKingCoordinate(board_, current_player_color_)
          .has_value()) {
    printCheckStatus();
  } else {
    view_.printInvalidMove();
  }

  return false;
}

void Game::printCheckStatus() const {
  const bool isInCheck =
      move_validator_.getCheckedKingCoordinate(board_, current_player_color_)
          .has_value();

  view_.printCheckStatus(getCurrentPlayer(), isInCheck);
}
