#include "Movement/MoveValidator.hpp"

bool MoveValidator::isValidMove(const Board &board, const Move &move,
                                Color color) const {
  Coordinate from = move.getFrom();
  Coordinate to = move.getTo();

  if (!board.isValidCoordinate(from) || !board.isValidCoordinate(to)) {
    return false;
  }

  if (from.getRow() == to.getRow() && from.getColumn() == to.getColumn()) {
    return false;
  }

  const Piece *piece = board.getPiece(from);
  if (piece == nullptr) {
    return false;
  }

  if (piece->getPieceColor() != color) {
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
