#include "Game/Game.hpp"

#include <iostream>
#include <map>

Game::Game()
    : white_player_(Color::White), black_player_(Color::Black),
      current_player_color_(Color::White), result_(GameResult::InProgress) {}

void Game::run() {
  printWelcomeMessage();

  if (!handleMainMenu()) {
    return;
  }

  setupGame();
  while (result_ == GameResult::InProgress) {
    handleTurn();
  }
  printResult();
}

bool Game::handleMainMenu() {
  while (true) {
    printMainMenu();
    std::cout << "> ";

    std::string input = input_normalizer_.normalize(input_reader_.readLine());

    if (input == "start") {
      return true;
    }

    if (input == "rules") {
      printRules();
      continue;
    }

    if (input == "help") {
      printHelp();
      continue;
    }

    if (input == "quit") {
      std::cout << "Goodbye." << std::endl;
      return false;
    }

    std::cout << "Invalid command." << std::endl;
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
    printTurnPrompt(current_player_color_);
    std::string input = input_normalizer_.normalize(input_reader_.readLine());

    const CommandResult command_result = handleCommand(input);
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
  std::optional<Move> move = move_parser_.handleMove(input);
  if (!move.has_value()) {
    return handleInvalidInput();
  }

  if (!move_validator_.isValidMove(board_, move.value(),
                                   current_player_color_)) {
    return handleInvalidMove();
  }

  const Move &valid_move = move.value();
  const Piece *moving_piece = board_.getPiece(valid_move.getFrom());
  if (moving_piece == nullptr) {
    return handleInvalidMove();
  }

  const Piece *captured_piece = board_.getPiece(valid_move.getTo());
  std::optional<PieceType> captured_piece_type = std::nullopt;
  if (captured_piece != nullptr) {
    captured_piece_type = captured_piece->getPieceType();
  }

  MoveRecord record(current_player_color_, valid_move.getFrom(),
                    valid_move.getTo(), moving_piece->getPieceType(),
                    captured_piece_type);

  executeMove(valid_move);
  move_history_.addRecord(record);
  finishTurnAfterMove();

  return true;
}

bool Game::isGameOver() const { return result_ != GameResult::InProgress; }

Game::CommandResult Game::handleCommand(const std::string &input) {
  static const std::map<std::string, CommandHandler> commands = {
      {"quit", &Game::handleQuit},         {"resign", &Game::handleResign},
      {"help", &Game::handleHelp},         {"rules", &Game::handleRules},
      {"check", &Game::handleCheck},       {"board", &Game::handleBoard},
      {"captured", &Game::handleCaptured}, {"draw", &Game::handleDrawOffer},
      {"moves", &Game::handleLegalMoves},  {"status", &Game::handleStatus},
      {"history", &Game::handleHistory}};
  const auto command = commands.find(input);
  if (command == commands.end()) {
    return CommandResult::NotCommand;
  }

  return (this->*(command->second))();
}

Game::CommandResult Game::handleQuit() {
  std::cout << getCurrentPlayer().getColorName()
            << ", quitting during a game counts as resignation." << std::endl;
  std::cout << "Are you sure? (yes/no): ";

  while (true) {
    std::string answer = input_normalizer_.normalize(input_reader_.readLine());

    if (answer == "yes") {
      std::cout << getCurrentPlayer().getColorName() << " quit the game."
                << std::endl;
      setWinnerByOpponent();
      return CommandResult::GameEnded;
    }

    if (answer == "no") {
      std::cout << "Quit cancelled." << std::endl;
      return CommandResult::Handled;
    }

    std::cout << "Please answer yes or no: ";
  }
}

Game::CommandResult Game::handleResign() {
  std::cout << getCurrentPlayer().getColorName() << " resigned." << std::endl;
  setWinnerByOpponent();
  return CommandResult::GameEnded;
}

Game::CommandResult Game::handleDrawOffer() {
  std::cout << getCurrentPlayer().getColorName() << " offered a draw."
            << std::endl;

  std::cout << getOpponentPlayer().getColorName()
            << ", accept draw? (yes/no): ";

  std::string answer = input_normalizer_.normalize(input_reader_.readLine());

  if (answer == "yes") {
    result_ = GameResult::Draw;
    return CommandResult::GameEnded;
  }

  if (answer == "no") {
    std::cout << "Draw offer declined." << std::endl;
    return CommandResult::Handled;
  }

  handleInvalidInput();
  return CommandResult::Handled;
}

Game::CommandResult Game::handleBoard() {
  renderer_.printBoard(
      board_, getCurrentPlayer(),
      move_validator_.getCheckedKingCoordinate(board_, current_player_color_));
  return CommandResult::Handled;
}

Game::CommandResult Game::handleHelp() {
  printHelp();
  return CommandResult::Handled;
}

Game::CommandResult Game::handleRules() {
  printRules();
  return CommandResult::Handled;
}

Game::CommandResult Game::handleCheck() {
  printCheckStatus();
  return CommandResult::Handled;
}

Game::CommandResult Game::handleCaptured() {
  printCapturedPieces();
  return CommandResult::Handled;
}

Game::CommandResult Game::handleLegalMoves() {
  while (true) {
    std::cout << "Enter square (or cancel): ";

    std::string input = input_normalizer_.normalize(input_reader_.readLine());
    if (input == "cancel") {
      return CommandResult::Handled;
    }

    std::optional<Coordinate> from = move_parser_.parseCoordinate(input);
    if (!from.has_value()) {
      handleInvalidInput();
      continue;
    }

    const Piece *piece = board_.getPiece(from.value());
    if (piece == nullptr) {
      std::cout << "There is no piece on this square." << std::endl;
      continue;
    }

    if (piece->getPieceColor() != current_player_color_) {
      std::cout << "Please choose your piece." << std::endl;
      continue;
    }

    std::vector<Coordinate> legal_moves = move_validator_.getLegalMovesForPiece(
        board_, from.value(), current_player_color_);

    if (legal_moves.empty()) {
      std::cout << "This piece has no legal moves." << std::endl;
      return CommandResult::Handled;
    }

    renderer_.printBoard(
        board_, getCurrentPlayer(),
        move_validator_.getCheckedKingCoordinate(board_, current_player_color_),
        legal_moves);

    return CommandResult::Handled;
  }
}

Game::CommandResult Game::handleStatus() {
  printStatus();
  return CommandResult::Handled;
}

Game::CommandResult Game::handleHistory() {
  move_history_.printHistory();
  return CommandResult::Handled;
}

void Game::executeMove(const Move &move) {
  if (move_validator_.isCastlingMove(board_, move, current_player_color_)) {
    executeCastling(move);
  } else {
    handleCapture(move);
    board_.movePiece(move);
    handlePromotion(move);
  }
  switchPlayer();
}

void Game::executeCastling(const Move &move) {
  Coordinate king_coord_from = move.getFrom();
  Coordinate king_coord_to = move.getTo();

  int column_difference = static_cast<int>(king_coord_to.getColumn()) -
                          static_cast<int>(king_coord_from.getColumn());

  std::size_t rook_from_column = 0;
  std::size_t rook_to_column = 0;

  if (column_difference > 0) {
    rook_from_column = 7;
    rook_to_column = 5;
  } else {
    rook_from_column = 0;
    rook_to_column = 3;
  }

  Coordinate rook_from(king_coord_from.getRow(), rook_from_column);
  Coordinate rook_to(king_coord_from.getRow(), rook_to_column);

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
    std::cout << "Checkmate!" << std::endl;
    setWinnerByOpponent();
    return;
  }

  if (move_validator_.isStalemate(board_, current_player_color_)) {
    std::cout << "Stalemate!" << std::endl;
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
  if (current_player_color_ == Color::White) {
    white_player_.addCapturedPiece(piece_type);
    white_player_.setScore(white_player_.getScore() +
                           getPieceValue(piece_type));
  } else {
    black_player_.addCapturedPiece(piece_type);
    black_player_.setScore(black_player_.getScore() +
                           getPieceValue(piece_type));
  }

  board_.removePiece(move.getTo());
}

void Game::handlePromotion(const Move &move) {
  Coordinate to = move.getTo();
  const Piece *piece = board_.getPiece(to);
  if (!canPromote(piece, to)) {
    return;
  }

  Player &player = getPlayerByColor(piece->getPieceColor());
  std::unique_ptr<Piece> new_piece =
      createPromotionPiece(piece->getPieceColor());

  const std::string promoted_piece_name =
      player.pieceTypeToString(new_piece->getPieceType());

  Piece *promoted_piece = player.promotePiece(piece, std::move(new_piece));

  if (promoted_piece != nullptr) {
    board_.setPiece(to, promoted_piece);
    std::cout << player.getColorName()
              << " pawn reached the last rank and was promoted to "
              << promoted_piece_name << "!" << std::endl;
  }
}

std::unique_ptr<Piece> Game::createPromotionPiece(Color color) {
  while (true) {
    std::cout << "Pawn promotion!" << std::endl;
    std::cout << "Choose piece:" << std::endl;
    std::cout << "  q - Queen" << std::endl;
    std::cout << "  r - Rook" << std::endl;
    std::cout << "  b - Bishop" << std::endl;
    std::cout << "  n - Knight" << std::endl;
    std::cout << "> ";

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
    std::cout << "Invalid promotion choice. Please choose queen, rook, "
                 "bishop, or knight."
              << std::endl;
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

void Game::setWinnerByOpponent() {
  result_ = current_player_color_ == Color::White ? GameResult::BlackWon
                                                  : GameResult::WhiteWon;
}

Player &Game::getPlayerByColor(Color color) {
  return color == Color::White ? white_player_ : black_player_;
}

const Player &Game::getCurrentPlayer() const {
  return current_player_color_ == Color::White ? white_player_ : black_player_;
}

const Player &Game::getOpponentPlayer() const {
  return current_player_color_ == Color::White ? black_player_ : white_player_;
}

int Game::getPieceValue(PieceType piece_type) const {
  switch (piece_type) {
  case PieceType::Pawn:
    return 1;
  case PieceType::Knight:
  case PieceType::Bishop:
    return 3;
  case PieceType::Rook:
    return 5;
  case PieceType::Queen:
    return 9;
  case PieceType::King:
    return 0;
  }
  return 0;
}

bool Game::handleInvalidInput() const {
  std::cout << "Invalid input." << std::endl;
  return false;
}

bool Game::handleInvalidMove() const {
  if (move_validator_.getCheckedKingCoordinate(board_, current_player_color_)
          .has_value()) {
    printCheckStatus();
  } else {
    std::cout << "Invalid move." << std::endl;
  }

  return false;
}

void Game::printWelcomeMessage() const {
  std::cout << std::endl;
  std::cout << "         WELCOME TO CHESS!         " << std::endl;
  std::cout << "          ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜          " << std::endl;
  std::cout << "          ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙          " << std::endl;
  std::cout << std::endl;
}

void Game::printMainMenu() const {
  std::cout << "Main menu:" << std::endl;
  std::cout << "  start  start a new game" << std::endl;
  std::cout << "  rules  show basic rules" << std::endl;
  std::cout << "  help   show commands" << std::endl;
  std::cout << "  quit   exit" << std::endl;
}

void Game::printTurnPrompt(Color color) const {
  if (color == Color::White) {
    std::cout << "White > ";
  } else if (color == Color::Black) {
    std::cout << "Black > ";
  }
}

void Game::printResult() const {
  if (result_ == GameResult::WhiteWon) {
    std::cout << "White won!" << std::endl;
  } else if (result_ == GameResult::BlackWon) {
    std::cout << "Black won!" << std::endl;
  } else if (result_ == GameResult::Draw) {
    std::cout << "The game ended in a draw." << std::endl;
  } else if (result_ == GameResult::Quit) {
    std::cout << getCurrentPlayer().getColorName() << " quit the game."
              << std::endl;
  }
}

void Game::printCheckStatus() const {
  if (move_validator_.getCheckedKingCoordinate(board_, current_player_color_)
          .has_value()) {
    std::cout << getCurrentPlayer().getColorName() << " is in check!"
              << std::endl;
  } else {
    std::cout << getCurrentPlayer().getColorName() << " is not in check."
              << std::endl;
  }
}

void Game::printHelp() const {
  std::cout << "Commands:" << std::endl;
  std::cout << "  e2 e4     move a piece" << std::endl;
  std::cout << "  board     print the board" << std::endl;
  std::cout << "  captured  show captured pieces" << std::endl;
  std::cout << "  help      show commands" << std::endl;
  std::cout << "  quit      exit the game, or resign during a game"
            << std::endl;
  std::cout << "  status    show current player, result, score and captures"
            << std::endl;
  std::cout << "  moves     show legal moves for selected square" << std::endl;
  std::cout << "  history   show move history" << std::endl;
  std::cout << "  undo      undo last move" << std::endl;
  std::cout << "  save      save game" << std::endl;
  std::cout << "  load      load game" << std::endl;
  std::cout << "  check     show if current player is in check" << std::endl;
  std::cout << "  rules     show input format and basic rules" << std::endl;
  std::cout << "  new       start a new game" << std::endl;
  std::cout << "  resign    resign the game" << std::endl;
  std::cout << "  draw      offer a draw" << std::endl;
  std::cout << "  restart   start a new game" << std::endl;
}

void Game::printRules() const {
  std::cout << std::endl << "Basic rules:" << std::endl;
  std::cout << "  Moves use this format: e2 e4" << std::endl;
  std::cout << "  White moves first." << std::endl;
  std::cout << "  You can only move your own pieces." << std::endl;
  std::cout << "  You cannot move onto your own piece." << std::endl;
  std::cout << "  Captures happen by moving onto an opponent piece."
            << std::endl;
  std::cout << std::endl;
  std::cout << "Piece movement:" << std::endl;
  std::cout << "  Pawn    moves forward, captures diagonally." << std::endl;
  std::cout << "  Knight  moves in an L shape and can jump." << std::endl;
  std::cout << "  Rook    moves horizontally or vertically." << std::endl;
  std::cout << "  Bishop  moves diagonally." << std::endl;
  std::cout << "  Queen   moves horizontally, vertically or diagonally."
            << std::endl;
  std::cout << "  King    moves one square in any direction." << std::endl;
  std::cout << std::endl;
  std::cout << "Ending the game:" << std::endl;
  std::cout << "  Checkmate: a king is in check and has no legal move."
            << std::endl;
  std::cout << "  Stalemate: the current player has no legal move, but is not "
               "in check."
            << std::endl;
  std::cout << "  Draw: both players agree that the game ends without a winner."
            << std::endl;
  std::cout << "  Resign: one player gives up, so the opponent wins."
            << std::endl;
  std::cout << std::endl;
}

void Game::printCapturedPieces() const {
  std::cout << "White captured: ";
  white_player_.printCapturedPieces();
  std::cout << std::endl;

  std::cout << "Black captured: ";
  black_player_.printCapturedPieces();
  std::cout << std::endl;
}

void Game::printStatus() const {
  std::cout << "Game status:" << std::endl;
  std::cout << "  Current player: " << getCurrentPlayer().getColorName()
            << std::endl;

  std::cout << "  Result: ";
  if (result_ == GameResult::InProgress) {
    std::cout << "In progress";
  } else if (result_ == GameResult::WhiteWon) {
    std::cout << "White won";
  } else if (result_ == GameResult::BlackWon) {
    std::cout << "Black won";
  } else if (result_ == GameResult::Draw) {
    std::cout << "Draw";
  } else if (result_ == GameResult::Quit) {
    std::cout << "Quit";
  }
  std::cout << std::endl;

  std::cout << "  Check: ";
  if (move_validator_.getCheckedKingCoordinate(board_, current_player_color_)
          .has_value()) {
    std::cout << "Yes";
  } else {
    std::cout << "No";
  }
  std::cout << std::endl;

  std::cout << "  White score: " << white_player_.getScore() << std::endl;
  std::cout << "  Black score: " << black_player_.getScore() << std::endl;
  printCapturedPieces();
}
