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

  if (piece->getPieceType() == PieceType::Pawn) {
    return isValidPawnMove(board, move, color);
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

bool MoveValidator::isValidPawnMove(const Board &board, const Move &move,
                                    Color color) const {
  const Piece *piece = board.getPiece(move.getFrom());

  if (piece == nullptr || piece->getPieceType() != PieceType::Pawn ||
      !isMovingOwnPiece(piece, color)) {
    return false;
  }

  const Coordinate &from = move.getFrom();
  const Coordinate &to = move.getTo();

  const int direction = color == Color::White ? -1 : 1;
  const int row_change =
      static_cast<int>(to.getRow()) - static_cast<int>(from.getRow());
  const int column_change =
      static_cast<int>(to.getColumn()) - static_cast<int>(from.getColumn());

  if (column_change == 0 && row_change == direction &&
      !board.isOccupied(to)) {
    return true;
  }

  if (column_change == 0 && row_change == direction * 2 &&
      isPawnOnStartingRank(piece, from)) {
    Coordinate middle_square(from.getRow() + direction, from.getColumn());
    return !board.isOccupied(middle_square) && !board.isOccupied(to);
  }

  if ((column_change == 1 || column_change == -1) &&
      row_change == direction) {
    return isOccupiedByEnemyPiece(board, to, color);
  }

  return false;
}

bool MoveValidator::isPawnOnStartingRank(const Piece *pawn,
                                         const Coordinate &from) const {
  if (pawn == nullptr || pawn->getPieceType() != PieceType::Pawn) {
    return false;
  }

  if (pawn->getPieceColor() == Color::White) {
    return from.getRow() == 6;
  }

  return from.getRow() == 1;
}
