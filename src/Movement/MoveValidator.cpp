#include "Movement/MoveValidator.hpp"

bool MoveValidator::isValidMove(const Board &board, const Move &move,
                                Color color) const {
  Coordinate from = move.getFrom();
  Coordinate to = move.getTo();

  if (!board.isValidCoordinate(from) || !board.isValidCoordinate(to)) {
    return false;
  }

  if (isSameSquare(move)) {
    return false;
  }

  const Piece *piece = board.getPiece(from);
  if (piece == nullptr) {
    return false;
  }

  if (!isMovingOwnPiece(piece, color)) {
    return false;
  }

  const Piece *target_piece = board.getPiece(to);
  if (target_piece != nullptr) {
    if (target_piece->getPieceColor() == color) {
      return false;
    }
    // capture
  }

  return true;
}

bool MoveValidator::isOccupiedByOwnPiece(const Board &board,
                                         const Coordinate &to,
                                         Color color) const {
  const Piece *target_piece = board.getPiece(to);

  return target_piece != nullptr && target_piece->getPieceColor() == color;
}

bool MoveValidator::isOccupiedByEnemyPiece(const Board &board,
                                           const Coordinate &to,
                                           Color color) const {
  const Piece *target_piece = board.getPiece(to);

  return target_piece != nullptr && target_piece->getPieceColor() != color;
}

bool MoveValidator::isMovingOwnPiece(const Piece *piece, Color color) const {
  return piece->getPieceColor() == color;
}

bool MoveValidator::isSameSquare(const Move &move) const {
  const Coordinate &from = move.getFrom();
  const Coordinate &to = move.getTo();

  return from.getRow() == to.getRow() && from.getColumn() == to.getColumn();
}

bool MoveValidator::isValidPawnMove() const {}
