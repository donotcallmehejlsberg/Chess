#ifndef MOVE_RECORD_HPP
#define MOVE_RECORD_HPP

#include <optional>

#include "Board/Coordinate.hpp"
#include "Color.hpp"
#include "PieceType.hpp"

class MoveRecord {
 private:
  Color player_color_;
  Coordinate from_;
  Coordinate to_;
  PieceType moved_piece_type_;
  std::optional<PieceType> captured_piece_type_;
  std::optional<PieceType> promoted_piece_type_;

 public:
  MoveRecord(Color player_color, const Coordinate &from, const Coordinate &to,
             PieceType moved_piece_type,
             std::optional<PieceType> captured_piece_type = std::nullopt,
             std::optional<PieceType> promoted_piece_type = std::nullopt);

  Color getPlayerColor() const;
  const Coordinate &getFrom() const;
  const Coordinate &getTo() const;
  PieceType getMovedPieceType() const;
  std::optional<PieceType> getCapturedPieceType() const;
  std::optional<PieceType> getPromotedPieceType() const;

  bool wasPawnDoubleMove() const;
};

#endif
