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

void Game::handleTurn() {
  printTurnPrompt(current_player_color_);
  std::string input = input_reader_.readLine();

  std::optional<Move> move = move_parser_.handleMove(input);
  if (!move.has_value()) {
    std::cout << "Invalid input." << std::endl;
    return;
  }

  bool valid_move =
      move_validator_.isValidMove(board_, move.value(), current_player_color_);
  if (valid_move == false) {
    std::cout << "Invalid move." << std::endl;
    return;
  }

  board_.movePiece(move.value());
  switchPlayer();
  renderer_.printBoard(board_, current_player_color_);
}

void Game::run() {
  std::cout << std::endl;
  std::cout << "         WELCOME TO CHESS!         " << std::endl;
  std::cout << "          ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜          " << std::endl;
  std::cout << "          ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙          " << std::endl;
  std::cout << std::endl;

  setupGame();
  while (result_ == GameResult::InProgress) {
    handleTurn();
  }
}
