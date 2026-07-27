#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <cstddef>

#include "Board/Coordinate.hpp"
#include "Color.hpp"
#include "Pieces/Piece.hpp"

class Square {
 private:
  Coordinate coordinate_;
  Piece *piece_;

 public:
  Square();
  Square(std::size_t row, std::size_t column);

  const Coordinate &getCoordinate() const;
  Color getSquareColor() const;

  const Piece *getPiece() const;
  void setPiece(Piece *piece);

  bool isOccupied() const;
  Piece *removePiece();
};

#endif