#include "Board/Board.hpp"

Board::Board() {
  for (std::size_t row = 0; row < Board::SIZE; row++) {
    for (std::size_t column = 0; column < Board::SIZE; column++) {
      squares_[row][column] = Square(row, column);
    }
  }
}

void Board::clear() {
  for (auto &row : squares_) {
    for (Square &square : row) {
      square.removePiece();
    }
  }
}

const Piece *Board::getPiece(const Coordinate &coordinate) const {
  return getSquare(coordinate).getPiece();
}

void Board::setPiece(const Coordinate &coordinate, Piece *piece) {
  getSquare(coordinate).setPiece(piece);
}

Piece *Board::removePiece(const Coordinate &coordinate) {
  return getSquare(coordinate).removePiece();
}

bool Board::isOccupied(const Coordinate &coordinate) const {
  return getSquare(coordinate).isOccupied();
}

const Square &Board::getSquare(const Coordinate &coordinate) const {
  return squares_[coordinate.getRow()][coordinate.getColumn()];
}

Square &Board::getSquare(const Coordinate &coordinate) {
  return squares_[coordinate.getRow()][coordinate.getColumn()];
}

bool Board::isValidCoordinate(const Coordinate &coordinate) const {
  return coordinate.getRow() < SIZE && coordinate.getColumn() < SIZE;
}

void Board::movePiece(const Move &move) {
  Coordinate from = move.getFrom();
  Coordinate to = move.getTo();

  if (!isValidCoordinate(from) || !isValidCoordinate(to)) {
    return;
  }

  const Piece *piece = getPiece(from);
  if (piece == nullptr) {
    return;
  }
  
  if(isOccupied(to))
  {
    return;
  }

  Piece *moving_piece = removePiece(from);
  setPiece(to, moving_piece);
}
