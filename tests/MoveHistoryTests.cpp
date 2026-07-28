#include <gtest/gtest.h>

#include "History/MoveHistory.hpp"

TEST(MoveHistoryTest, IsEmptyInitially) {
  MoveHistory move_history;

  EXPECT_TRUE(move_history.isEmpty());
}

TEST(MoveHistoryTest, HasNoLastRecordInitially) {
  MoveHistory move_history;
  const std::optional<MoveRecord> record = move_history.getLastRecord();

  EXPECT_FALSE(record.has_value());
}

TEST(MoveHistoryTest, IsNotEmptyAfterAddingRecord) {
  MoveHistory move_history;
  const Coordinate from(6, 4);
  const Coordinate to(4, 4);

  const MoveRecord record(Color::White, from, to, PieceType::Pawn);

  move_history.addRecord(record);

  EXPECT_FALSE(move_history.isEmpty());
}

TEST(MoveHistoryTest, ReturnsLastAddedRecord) {
  MoveHistory move_history;

  const Coordinate first_from(6, 4);
  const Coordinate first_to(4, 4);
  
  const Coordinate second_from(0, 1);
  const Coordinate second_to(2, 2);

  const MoveRecord first_record(Color::White, first_from, first_to,
                                PieceType::Pawn);
  const MoveRecord second_record(Color::Black, second_from, second_to,
                                 PieceType::Knight);

  move_history.addRecord(first_record);
  move_history.addRecord(second_record);

  const std::optional<MoveRecord> last_record = move_history.getLastRecord();

  ASSERT_TRUE(last_record.has_value());

  const MoveRecord &record = last_record.value();

  EXPECT_EQ(Color::Black, record.getPlayerColor());
  EXPECT_EQ(PieceType::Knight, record.getMovedPieceType());
  EXPECT_EQ(0U, record.getFrom().getRow());
  EXPECT_EQ(1U, record.getFrom().getColumn());
  EXPECT_EQ(2U, record.getTo().getRow());
  EXPECT_EQ(2U, record.getTo().getColumn());
}
