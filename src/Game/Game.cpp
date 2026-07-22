#include "Game/Game.hpp"

#include <iostream>

Game::Game()
    : white_player_(Color::White), black_player_(Color::Black),
      current_player_color_(Color::White), result_(GameResult::InProgress) {}

void Game::printResult() const {
  if (result_ == GameResult::WhiteWon) {
    std::cout << "White won!" << std::endl;
  } else if (result_ == GameResult::BlackWon) {
    std::cout << "Black won!" << std::endl;
  } else if (result_ == GameResult::Draw) {
    std::cout << "Draw!" << std::endl;
  } else if (result_ == GameResult::Quit) {
    std::cout << getCurrentPlayer().getColorName() << " quit the game."
              << std::endl;
  }
}

bool Game::isGameOver() const { return result_ != GameResult::InProgress; }

void Game::setupGame() {
  result_ = GameResult::InProgress;
  current_player_color_ = Color::White;
  setup_.setupPieces(board_, white_player_, black_player_);
  renderer_.printBoard(board_, white_player_);
}

void Game::switchPlayer() {
  if (current_player_color_ == Color::White) {
    current_player_color_ = Color::Black;
  } else {
    current_player_color_ = Color::White;
  }
}

void Game::printTurnPrompt(Color color) {
  if (color == Color::White) {
    std::cout << "White > ";
  } else if (color == Color::Black) {
    std::cout << "Black > ";
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
  std::cout << "  quit      exit the game" << std::endl;
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

void Game::printMainMenu() const {
  std::cout << "Main menu:" << std::endl;
  std::cout << "  start  start a new game" << std::endl;
  std::cout << "  rules  show basic rules" << std::endl;
  std::cout << "  help   show commands" << std::endl;
  std::cout << "  quit   exit" << std::endl;
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

void Game::handleTurn() {
  while (true) {
    printTurnPrompt(current_player_color_);
    std::string input = input_normalizer_.normalize(input_reader_.readLine());
    if (input == "quit") {
      result_ = GameResult::Quit;
      return;
    }

    if (input == "resign") {
      std::cout << getCurrentPlayer().getColorName() << " resigned."
                << std::endl;
      result_ = current_player_color_ == Color::White ? GameResult::BlackWon
                                                      : GameResult::WhiteWon;
      return;
    }

    if (input == "help") {
      printHelp();
      continue;
    }

    if (input == "rules") {
      printRules();
      continue;
    }

    if (input == "check") {
      printCheckStatus();
      continue;
    }

    if (input == "board") {
      renderer_.printBoard(board_, getCurrentPlayer(),
                           move_validator_.getCheckedKingCoordinate(
                               board_, current_player_color_));
      continue;
    }

    if (input == "captured") {
      std::cout << "White captured: ";
      white_player_.printCapturedPieces();
      std::cout << std::endl;

      std::cout << "Black captured: ";
      black_player_.printCapturedPieces();
      std::cout << std::endl;

      continue;
    }

    std::optional<Move> move = move_parser_.handleMove(input);
    if (!move.has_value()) {
      std::cout << "Invalid input." << std::endl;
      continue;
    }

    bool valid_move = move_validator_.isValidMove(board_, move.value(),
                                                  current_player_color_);
    if (valid_move == false) {
      if (move_validator_
              .getCheckedKingCoordinate(board_, current_player_color_)
              .has_value()) {
        printCheckStatus();
      } else {
        std::cout << "Invalid move." << std::endl;
      }
      continue;
    }
    handleCapture(move.value());
    board_.movePiece(move.value());
    switchPlayer();

    std::optional<Coordinate> checked_king =
        move_validator_.getCheckedKingCoordinate(board_, current_player_color_);
    renderer_.printBoard(board_, getCurrentPlayer(), checked_king);

    if (move_validator_.isCheckmate(board_, current_player_color_)) {
      printCheckStatus();
      std::cout << "Checkmate!" << std::endl;
      if (current_player_color_ == Color::White) {
        result_ = GameResult::BlackWon;
        return;
      } else if (current_player_color_ == Color::Black) {
        result_ = GameResult::WhiteWon;
        return;
      }
    }

    if (move_validator_.isStalemate(board_, current_player_color_)) {
      std::cout << "Stalemate!" << std::endl;
      result_ = GameResult::Draw;
      return;
    }

    if (checked_king.has_value()) {
      printCheckStatus();
    }
    return;
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
  } else {
    black_player_.addCapturedPiece(piece_type);
  }

  board_.removePiece(move.getTo());
}

const Player &Game::getCurrentPlayer() const {
  return current_player_color_ == Color::White ? white_player_ : black_player_;
}

void Game::run() {
  std::cout << std::endl;
  std::cout << "         WELCOME TO CHESS!         " << std::endl;
  std::cout << "          ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜          " << std::endl;
  std::cout << "          ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙          " << std::endl;
  std::cout << std::endl;

  if (!handleMainMenu()) {
    return;
  }

  setupGame();
  while (result_ == GameResult::InProgress) {
    handleTurn();
  }
  printResult();
}
