#ifndef BOARD_RENDERER_HPP
#define BOARD_RENDERER_HPP

#include "Board/Board.hpp"

class Player;

class BoardRenderer {
public:
  void printBoard(const Board &board, const Player &current_player) const;

private:
  void printSquare(const Square &square) const;
  void printPiece(const Square &square) const;
  void printColumnLabels(Color color) const;
};

#endif
