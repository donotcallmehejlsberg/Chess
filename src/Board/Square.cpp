#include "Board/Square.hpp"

Square::Square(std::size_t row, std::size_t column)
    : coordinate_(row, column), piece_(nullptr) {}

Square::Square() : coordinate_(0, 0), piece_(nullptr) {}

const Coordinate &Square::getCoordinate() const { return coordinate_; }

Color Square::getSquareColor() const {
  std::size_t sum = coordinate_.getRow() + coordinate_.getColumn();
  return sum % 2 == 0 ? Color::White : Color::Black;
}

const Piece *Square::getPiece() const { return piece_; }

void Square::setPiece(Piece *piece) { piece_ = piece; }

bool Square::isOccupied() const { return piece_ != nullptr; }

Piece *Square::removePiece() {
  Piece *removed_piece = piece_;
  piece_ = nullptr;
  return removed_piece;
}
