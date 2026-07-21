#include "Movement/MoveValidator.hpp"
#include <cstdlib>

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

  if (isOccupiedByOwnPiece(board, to, color)) {
    return false;
  }

  if (piece->getPieceType() == PieceType::Pawn) {
    return isValidPawnMove(board, move, color);
  }

  if (piece->getPieceType() == PieceType::Knight) {
    return isValidKnightMove(board, move, color);
  }

  if (piece->getPieceType() == PieceType::Rook) {
    return isValidRookMove(board, move, color);
  }

  if (piece->getPieceType() == PieceType::Bishop) {
    return isValidBishopMove(board, move, color);
  }

  if (piece->getPieceType() == PieceType::Queen) {
    return isValidQueenMove(board, move, color);
  }

  if (piece->getPieceType() == PieceType::King) {
    return isValidKingMove(board, move, color);
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

bool MoveValidator::isValidQueenMove(const Board &board, const Move &move,
                                     Color color) const {
  const Piece *queen = board.getPiece(move.getFrom());

  if (queen == nullptr || queen->getPieceType() != PieceType::Queen ||
      !isMovingOwnPiece(queen, color)) {
    return false;
  }

  const Coordinate &from = move.getFrom();
  const Coordinate &to = move.getTo();

  const int row_change =
      static_cast<int>(to.getRow()) - static_cast<int>(from.getRow());
  const int column_change =
      static_cast<int>(to.getColumn()) - static_cast<int>(from.getColumn());

  if ((row_change == 0 && column_change != 0) ||
      (column_change == 0 && row_change != 0) ||
      (std::abs(row_change) == std::abs(column_change))) {
    return isPathClear(board, move);
  }

  return false;
}

bool MoveValidator::isValidBishopMove(const Board &board, const Move &move,
                                      Color color) const {
  const Piece *bishop = board.getPiece(move.getFrom());

  if (bishop == nullptr || bishop->getPieceType() != PieceType::Bishop ||
      !isMovingOwnPiece(bishop, color)) {
    return false;
  }

  const Coordinate &from = move.getFrom();
  const Coordinate &to = move.getTo();

  const int row_change =
      static_cast<int>(to.getRow()) - static_cast<int>(from.getRow());
  const int column_change =
      static_cast<int>(to.getColumn()) - static_cast<int>(from.getColumn());

  if (std::abs(row_change) == std::abs(column_change)) {
    return isPathClear(board, move);
  }

  return false;
}

bool MoveValidator::isValidRookMove(const Board &board, const Move &move,
                                    Color color) const {
  const Piece *rook = board.getPiece(move.getFrom());

  if (rook == nullptr || rook->getPieceType() != PieceType::Rook ||
      !isMovingOwnPiece(rook, color)) {
    return false;
  }

  const Coordinate &from = move.getFrom();
  const Coordinate &to = move.getTo();

  const int row_change =
      static_cast<int>(to.getRow()) - static_cast<int>(from.getRow());
  const int column_change =
      static_cast<int>(to.getColumn()) - static_cast<int>(from.getColumn());

  if ((row_change == 0 && column_change != 0) ||
      (column_change == 0 && row_change != 0)) {
    return isPathClear(board, move);
  }

  return false;
}

bool MoveValidator::isValidKingMove(const Board &board, const Move &move,
                                    Color color) const {
  const Piece *king = board.getPiece(move.getFrom());

  if (king == nullptr || king->getPieceType() != PieceType::King ||
      !isMovingOwnPiece(king, color)) {
    return false;
  }

  const Coordinate &from = move.getFrom();
  const Coordinate &to = move.getTo();

  const int row_change =
      static_cast<int>(to.getRow()) - static_cast<int>(from.getRow());
  const int column_change =
      static_cast<int>(to.getColumn()) - static_cast<int>(from.getColumn());

  if (std::abs(row_change) <= 1 && std::abs(column_change) <= 1) {
    return true;
  }

  return false;
}

bool MoveValidator::isValidKnightMove(const Board &board, const Move &move,
                                      Color color) const {
  const Piece *knight = board.getPiece(move.getFrom());

  if (knight == nullptr || knight->getPieceType() != PieceType::Knight ||
      !isMovingOwnPiece(knight, color)) {
    return false;
  }

  const Coordinate &from = move.getFrom();
  const Coordinate &to = move.getTo();

  const int row_change =
      static_cast<int>(to.getRow()) - static_cast<int>(from.getRow());
  const int column_change =
      static_cast<int>(to.getColumn()) - static_cast<int>(from.getColumn());

  if ((std::abs(row_change) == 2 && std::abs(column_change) == 1) ||
      (std::abs(row_change) == 1 && std::abs(column_change) == 2)) {
    return true;
  }

  return false;
}

bool MoveValidator::isValidPawnMove(const Board &board, const Move &move,
                                    Color color) const {
  const Piece *pawn = board.getPiece(move.getFrom());

  if (pawn == nullptr || pawn->getPieceType() != PieceType::Pawn ||
      !isMovingOwnPiece(pawn, color)) {
    return false;
  }

  const Coordinate &from = move.getFrom();
  const Coordinate &to = move.getTo();

  const int direction = color == Color::White ? -1 : 1;
  const int row_change =
      static_cast<int>(to.getRow()) - static_cast<int>(from.getRow());
  const int column_change =
      static_cast<int>(to.getColumn()) - static_cast<int>(from.getColumn());

  if (column_change == 0 && row_change == direction && !board.isOccupied(to)) {
    return true;
  }

  if (column_change == 0 && row_change == direction * 2 &&
      isPawnOnStartingRank(pawn, from)) {
    Coordinate middle_square(from.getRow() + direction, from.getColumn());
    return !board.isOccupied(middle_square) && !board.isOccupied(to);
  }

  if ((column_change == 1 || column_change == -1) && row_change == direction) {
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

bool MoveValidator::isPathClear(const Board &board, const Move &move) const {
  const Coordinate &from = move.getFrom();
  const Coordinate &to = move.getTo();

  int row_step = 0;
  int column_step = 0;

  if (to.getRow() > from.getRow()) {
    row_step = 1;
  } else if (to.getRow() < from.getRow()) {
    row_step = -1;
  }

  if (to.getColumn() > from.getColumn()) {
    column_step = 1;
  } else if (to.getColumn() < from.getColumn()) {
    column_step = -1;
  }

  int current_row = static_cast<int>(from.getRow()) + row_step;
  int current_column = static_cast<int>(from.getColumn()) + column_step;

  while (current_row != static_cast<int>(to.getRow()) ||
         current_column != static_cast<int>(to.getColumn())) {
    Coordinate current(current_row, current_column);

    if (board.isOccupied(current)) {
      return false;
    }

    current_row += row_step;
    current_column += column_step;
  }

  return true;
}
