#ifndef BOARD_RENDERER_HPP
#define BOARD_RENDERER_HPP

#include <optional>
#include <vector>

#include "Board/Board.hpp"

class Player;

class BoardRenderer {
 public:
  void printBoard(const Board &board, const Player &current_player) const;
  void printBoard(
      const Board &board, const Player &current_player,
      const std::optional<Coordinate> &checked_king_coordinate) const;
  void printBoard(const Board &board, const Player &current_player,
                  const std::optional<Coordinate> &checked_king_coordinate,
                  const std::vector<Coordinate> &legal_move_coordinates) const;

 private:
  void printSquare(const Square &square,
                   const std::optional<Coordinate> &checked_king_coordinate,
                   const std::vector<Coordinate> &legal_move_coordinates) const;
  void printPiece(const Square &square) const;
  void printColumnLabels(Color color) const;
  bool isHighlightedSquare(
      const Square &square,
      const std::optional<Coordinate> &checked_king_coordinate) const;

  bool isLegalMoveSquare(
      const Square &square,
      const std::vector<Coordinate> &legal_move_coordinates) const;
};

#endif
