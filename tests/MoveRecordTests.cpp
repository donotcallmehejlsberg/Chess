#include <gtest/gtest.h>

#include <optional>

#include "History/MoveRecord.hpp"

TEST(MoveRecordTest, StoresBasicMoveData) {
  const Coordinate from(6, 4);
  const Coordinate to(4, 4);

  const MoveRecord record(Color::White, from, to, PieceType::Pawn);

  EXPECT_EQ(Color::White, record.getPlayerColor());
  EXPECT_EQ(6, record.getFrom().getRow());
  EXPECT_EQ(4, record.getFrom().getColumn());
  EXPECT_EQ(4, record.getTo().getRow());
  EXPECT_EQ(4, record.getTo().getColumn());
  EXPECT_EQ(PieceType::Pawn, record.getMovedPieceType());
}

TEST(MoveRecordTest, HasNoCaptureByDefault) {
  const Coordinate from(6, 4);
  const Coordinate to(4, 4);

  const MoveRecord record(Color::White, from, to, PieceType::Pawn);
  const std::optional<PieceType> captured_piece = record.getCapturedPieceType();

  EXPECT_FALSE(captured_piece.has_value());
}

TEST(MoveRecordTest, StoresCapturedPiece) {
  const Coordinate from(6, 4);
  const Coordinate to(4, 4);

  const MoveRecord record(Color::White, from, to, PieceType::Pawn,
                          PieceType::Knight);
  const std::optional<PieceType> captured_piece = record.getCapturedPieceType();

  ASSERT_TRUE(captured_piece.has_value());
  EXPECT_EQ(PieceType::Knight, captured_piece.value());
}

TEST(MoveRecordTest, StoresPromotedPiece) {
  const Coordinate from(6, 4);
  const Coordinate to(4, 4);

  const MoveRecord record(Color::White, from, to, PieceType::Pawn,
                          PieceType::Knight, PieceType::Queen);
  const std::optional<PieceType> promoted_piece = record.getPromotedPieceType();

  ASSERT_TRUE(promoted_piece.has_value());
  EXPECT_EQ(PieceType::Queen, promoted_piece.value());
}

TEST(MoveRecordTest, DetectsPawnDoubleMove) {
  const Coordinate from(6, 4);
  const Coordinate to(4, 4);

  const MoveRecord record(Color::White, from, to, PieceType::Pawn);
  EXPECT_TRUE(record.wasPawnDoubleMove());
}

TEST(MoveRecordTest, RejectsNonPawnAsPawnDoubleMove) {
  const Coordinate from(6, 4);
  const Coordinate to(4, 4);

  const MoveRecord record(Color::White, from, to, PieceType::Rook);
  EXPECT_FALSE(record.wasPawnDoubleMove());
}
