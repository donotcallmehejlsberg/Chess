#include "History/MoveRecord.hpp"

#include <cstdlib>

MoveRecord::MoveRecord(Color player_color, const Coordinate &from,
                       const Coordinate &to, PieceType moved_piece_type,
                       std::optional<PieceType> captured_piece_type,
                       std::optional<PieceType> promoted_piece_type)
    : player_color_(player_color),
      from_(from),
      to_(to),
      moved_piece_type_(moved_piece_type),
      captured_piece_type_(captured_piece_type),
      promoted_piece_type_(promoted_piece_type) {}

Color MoveRecord::getPlayerColor() const { return player_color_; }

const Coordinate &MoveRecord::getFrom() const { return from_; }

const Coordinate &MoveRecord::getTo() const { return to_; }

PieceType MoveRecord::getMovedPieceType() const { return moved_piece_type_; }

std::optional<PieceType> MoveRecord::getCapturedPieceType() const {
  return captured_piece_type_;
}

std::optional<PieceType> MoveRecord::getPromotedPieceType() const {
  return promoted_piece_type_;
}

bool MoveRecord::wasPawnDoubleMove() const {
  if (moved_piece_type_ != PieceType::Pawn) {
    return false;
  }

  if (to_.getColumn() != from_.getColumn()) {
    return false;
  }

  const int row_change =
      static_cast<int>(to_.getRow()) - static_cast<int>(from_.getRow());

  if (std::abs(row_change) != 2) {
    return false;
  }

  return true;
}
