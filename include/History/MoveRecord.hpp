#ifndef MOVE_RECORD_HPP
#define MOVE_RECORD_HPP

#include "Board/Coordinate.hpp"
#include "Color.hpp"
#include "PieceType.hpp"

#include <optional>

class MoveRecord {
private:
  Color player_color_;
  Coordinate from_;
  Coordinate to_;
  PieceType moved_piece_;
  std::optional<PieceType> captured_piece_;
  std::optional<PieceType> promoted_to_;

public:
  MoveRecord(Color player_color, const Coordinate &from, const Coordinate &to,
             PieceType moved_piece,
             std::optional<PieceType> captured_piece = std::nullopt,
             std::optional<PieceType> promoted_to = std::nullopt);

  Color getPlayerColor() const;
  const Coordinate &getFrom() const;
  const Coordinate &getTo() const;
  PieceType getMovedPiece() const;
  std::optional<PieceType> getCapturedPiece() const;
  std::optional<PieceType> getPromotedTo() const;

  bool wasPawnDoubleMove() const;
};

#endif
