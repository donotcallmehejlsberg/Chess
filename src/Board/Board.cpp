#include "Board/Board.hpp"

#include <stdexcept>

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
  if (!isValidCoordinate(coordinate)) {
    return nullptr;
  }

  return getSquare(coordinate).getPiece();
}

void Board::setPiece(const Coordinate &coordinate, Piece *piece) {
  if (!isValidCoordinate(coordinate)) {
    return;
  }

  getSquare(coordinate).setPiece(piece);
}

Piece *Board::removePiece(const Coordinate &coordinate) {
  if (!isValidCoordinate(coordinate)) {
    return nullptr;
  }

  return getSquare(coordinate).removePiece();
}

bool Board::isOccupied(const Coordinate &coordinate) const {
  if (!isValidCoordinate(coordinate)) {
    return false;
  }

  return getSquare(coordinate).isOccupied();
}

const Square &Board::getSquare(const Coordinate &coordinate) const {
  if (!isValidCoordinate(coordinate)) {
    throw std::out_of_range("Board coordinate is out of range");
  }

  return squares_[coordinate.getRow()][coordinate.getColumn()];
}

Square &Board::getSquare(const Coordinate &coordinate) {
  if (!isValidCoordinate(coordinate)) {
    throw std::out_of_range("Board coordinate is out of range");
  }

  return squares_[coordinate.getRow()][coordinate.getColumn()];
}

bool Board::isValidCoordinate(const Coordinate &coordinate) const {
  return coordinate.getRow() < SIZE && coordinate.getColumn() < SIZE;
}

void Board::movePiece(const Move &move) {
  if (!isValidCoordinate(move.getFrom()) || !isValidCoordinate(move.getTo())) {
    return;
  }

  Piece *moving_piece = removePiece(move.getFrom());
  if (moving_piece == nullptr) {
    return;
  }

  moving_piece->markMoved();
  setPiece(move.getTo(), moving_piece);
}
