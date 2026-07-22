#ifndef BOARD_RENDERER_HPP
#define BOARD_RENDERER_HPP

#include "Board/Board.hpp"

#include <optional>

class Player;

class BoardRenderer {
public:
  void printBoard(const Board &board, const Player &current_player) const;
  void
  printBoard(const Board &board, const Player &current_player,
             const std::optional<Coordinate> &highlighted_coordinate) const;

private:
  void
  printSquare(const Square &square,
              const std::optional<Coordinate> &highlighted_coordinate) const;
  void printPiece(const Square &square) const;
  void printColumnLabels(Color color) const;
  bool isHighlightedSquare(
      const Square &square,
      const std::optional<Coordinate> &highlighted_coordinate) const;
};

#endif
