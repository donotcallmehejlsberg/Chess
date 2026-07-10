#include "Board/Board.hpp"
#include "Board/BoardRenderer.hpp"
#include "Game/GameSetup.hpp"
#include "Player.hpp"

int main() {
  Player white_player(Color::White);
  Player black_player(Color::Black);

  Board board;
  GameSetup setup;
  BoardRenderer renderer;

  setup.setupPieces(board, white_player, black_player);
  renderer.printBoard(board, white_player);

  return 0;
}
