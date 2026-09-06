#include "Game/GameView.hpp"

#include <iostream>

void GameView::printWelcomeMessage() const {
  std::cout << std::endl;
  std::cout << "         WELCOME TO CHESS!         " << std::endl;
  std::cout << "          ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜          " << std::endl;
  std::cout << "          ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙          " << std::endl;
  std::cout << std::endl;
}

void GameView::printMainMenu() const {
  std::cout << "Main menu:" << std::endl;
  std::cout << "  start  start a new game" << std::endl;
  std::cout << "  rules  show basic rules" << std::endl;
  std::cout << "  help   show commands" << std::endl;
  std::cout << "  quit   exit" << std::endl;
}

void GameView::printHelp() const {
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
  std::cout << "  check     show if current player is in check" << std::endl;
  std::cout << "  rules     show input format and basic rules" << std::endl;
  std::cout << "  resign    resign the game" << std::endl;
  std::cout << "  draw      offer a draw" << std::endl;
}

void GameView::printRules() const {
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
