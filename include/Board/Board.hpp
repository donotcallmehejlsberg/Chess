#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <cstddef>

#include "Board/Coordinate.hpp"
#include "Board/Square.hpp"
#include "Pieces/Piece.hpp"
#include "Movement/Move.hpp"

class Board {
public:
  static constexpr std::size_t SIZE = 8;

private:
  std::array<std::array<Square, SIZE>, SIZE> squares_;
  Square &getSquare(const Coordinate &coordinate);

public:
  Board();

  void clear();

  const Piece *getPiece(const Coordinate &coordinate) const;
  void setPiece(const Coordinate &coordinate, Piece *piece);

  void movePiece(const Move &move);

  Piece *removePiece(const Coordinate &coordinate);
  bool isOccupied(const Coordinate &coordinate) const;
  bool isValidCoordinate(const Coordinate &coordinate) const;

  const Square &getSquare(const Coordinate &coordinate) const;
};

#endif
