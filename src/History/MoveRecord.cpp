#include "History/MoveRecord.hpp"

#include <cstdlib>

MoveRecord::MoveRecord(Color player_color, const Coordinate &from,
                       const Coordinate &to, PieceType moved_piece,
                       std::optional<PieceType> captured_piece,
                       std::optional<PieceType> promoted_to)
    : player_color_(player_color),
      from_(from),
      to_(to),
      moved_piece_(moved_piece),
      captured_piece_(captured_piece),
      promoted_to_(promoted_to) {}

Color MoveRecord::getPlayerColor() const { return player_color_; }

const Coordinate &MoveRecord::getFrom() const { return from_; }

const Coordinate &MoveRecord::getTo() const { return to_; }

PieceType MoveRecord::getMovedPiece() const { return moved_piece_; }

std::optional<PieceType> MoveRecord::getCapturedPiece() const {
  return captured_piece_;
}

std::optional<PieceType> MoveRecord::getPromotedTo() const {
  return promoted_to_;
}

bool MoveRecord::wasPawnDoubleMove() const {
  if (moved_piece_ != PieceType::Pawn) {
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
