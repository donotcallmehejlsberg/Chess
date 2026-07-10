#include "Board/Board.hpp"
#include "Board/BoardRenderer.hpp"
#include "Game/GameSetup.hpp"
#include "Movement/Move.hpp"
#include "Player.hpp"

#include <iostream>

int main() {
  Player white_player(Color::White);
  Player black_player(Color::Black);

  Board board;
  GameSetup setup;
  BoardRenderer renderer;

  setup.setupPieces(board, white_player, black_player);

  std::cout << "Before move E2 -> E4:" << std::endl;
  renderer.printBoard(board, white_player);

  Move move(Coordinate(6, 4), Coordinate(4, 4));
  board.movePiece(move);

  std::cout << "After move E2 -> E4:" << std::endl;
  renderer.printBoard(board, white_player);

  return 0;
}
