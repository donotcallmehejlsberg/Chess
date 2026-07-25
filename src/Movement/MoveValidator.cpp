#include "Movement/MoveValidator.hpp"
#include <cstdlib>

bool MoveValidator::isValidMove(const Board &board, const Move &move,
                                Color color) const {
  if (!isPieceMoveValid(board, move, color)) {
    return false;
  }

  if (wouldLeaveKingInCheck(board, move, color)) {
    return false;
  }

  return true;
}

bool MoveValidator::isPieceMoveValid(const Board &board, const Move &move,
                                     Color color) const {
  const Coordinate &from = move.getFrom();
  const Coordinate &to = move.getTo();

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

  return false;
}

bool MoveValidator::wouldLeaveKingInCheck(Board board, const Move &move,
                                          Color color) const {
  const Coordinate &from = move.getFrom();
  const Coordinate &to = move.getTo();

  Piece *moving_piece = board.removePiece(from);
  board.removePiece(to);
  board.setPiece(to, moving_piece);

  return isKingInCheck(board, color);
}

bool MoveValidator::isKingInCheck(const Board &board, Color color) const {

  std::optional<Coordinate> king_coordinate = findKingCoordinate(board, color);

  if (!king_coordinate.has_value()) {
    return false;
  }

  Coordinate king_coord = king_coordinate.value();
  Color enemy_color = color == Color::White ? Color::Black : Color::White;

  for (std::size_t row = 0; row < Board::SIZE; row++) {
    for (std::size_t column = 0; column < Board::SIZE; column++) {
      Coordinate coord(row, column);
      const Piece *opponent_piece = board.getPiece(coord);

      if (opponent_piece == nullptr) {
        continue;
      }

      if (opponent_piece->getPieceColor() != enemy_color) {
        continue;
      }

      Move attack_move(coord, king_coord);

      if (isPieceMoveValid(board, attack_move, enemy_color)) {
        return true;
      }
    }
  }

  return false;
}

std::vector<Coordinate>
MoveValidator::getLegalMovesForPiece(const Board &board, const Coordinate &from,
                                     Color color) const {
  std::vector<Coordinate> legal_moves;
  const Piece *piece = board.getPiece(from);
  if (piece == nullptr) {
    return legal_moves;
  }

  if (piece->getPieceColor() != color) {
    return legal_moves;
  }

  for (std::size_t row = 0; row < Board::SIZE; row++) {
    for (std::size_t column = 0; column < Board::SIZE; column++) {
      Coordinate to(row, column);
      Move move(from, to);

      if (isValidMove(board, move, color)) {
        legal_moves.push_back(to);
      }
    }
  }
  return legal_moves;
}

std::optional<Coordinate>
MoveValidator::getCheckedKingCoordinate(const Board &board, Color color) const {
  if (!isKingInCheck(board, color)) {
    return std::nullopt;
  }

  return findKingCoordinate(board, color);
}

std::optional<Coordinate> MoveValidator::findKingCoordinate(const Board &board,
                                                            Color color) const {
  for (std::size_t row = 0; row < Board::SIZE; row++) {
    for (std::size_t column = 0; column < Board::SIZE; column++) {
      Coordinate coordinate(row, column);
      const Piece *piece = board.getPiece(coordinate);

      if (piece == nullptr) {
        continue;
      }

      if (piece->getPieceType() == PieceType::King &&
          piece->getPieceColor() == color) {
        return coordinate;
      }
    }
  }
  return std::nullopt;
}

bool MoveValidator::hasAnyLegalMove(const Board &board, Color color) const {
  for (std::size_t from_row = 0; from_row < Board::SIZE; from_row++) {
    for (std::size_t from_column = 0; from_column < Board::SIZE;
         from_column++) {
      Coordinate from(from_row, from_column);
      const Piece *piece = board.getPiece(from);
      if (piece == nullptr) {
        continue;
      }

      if (piece->getPieceColor() != color) {
        continue;
      }

      for (std::size_t to_row = 0; to_row < Board::SIZE; to_row++) {
        for (std::size_t to_column = 0; to_column < Board::SIZE; to_column++) {
          Coordinate to(to_row, to_column);

          Move possible_move(from, to);

          if (isValidMove(board, possible_move, color)) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool MoveValidator::isCheckmate(const Board &board, Color color) const {
  if (isKingInCheck(board, color) && !hasAnyLegalMove(board, color)) {
    return true;
  }
  return false;
}

bool MoveValidator::isStalemate(const Board &board, Color color) const {
  if (!isKingInCheck(board, color) && !hasAnyLegalMove(board, color)) {
    return true;
  }
  return false;
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

bool MoveValidator::isValidCastlingMove(const Board &board, const Move &move,
                                        Color color) {
  Coordinate king_coord_from = move.getFrom();
  Coordinate king_coord_to = move.getTo();

  const Piece *king = board.getPiece(king_coord_from);
  if (king == nullptr || king->getPieceType() != PieceType::King ||
      king->getPieceColor() != color) {
    return false;
  }

  if (king_coord_from.getRow() != king_coord_to.getRow()) {
    return false;
  }

  int column_difference = static_cast<int>(king_coord_to.getColumn()) -
                          static_cast<int>(king_coord_from.getColumn());

  if (std::abs(column_difference) != 2) {
    return false;
  }

  return true;
}
