#include <gtest/gtest.h>

#include "Movement/MoveParser.hpp"

TEST(MoveParserTest, ValidLength) {
  MoveParser move_parser;
  const std::string input = "e2 e4";

  const bool is_valid = move_parser.hasValidLength(input);

  EXPECT_TRUE(is_valid);
}

TEST(MoveParserTest, InvalidLength) {
  MoveParser move_parser;
  const std::string input = "e2 e44";

  const bool is_valid = move_parser.hasValidLength(input);

  EXPECT_FALSE(is_valid);
}

TEST(MoveParserTest, ProducesCorrectCoordinates) {
  MoveParser move_parser;
  const std::string input = "e2 e4";

  const std::optional<Move> result = move_parser.parseMove(input);
  ASSERT_TRUE(result.has_value());

  const Move &move = result.value();

  const Coordinate &from = move.getFrom();
  const Coordinate &to = move.getTo();

  EXPECT_EQ(6, from.getRow());
  EXPECT_EQ(4, from.getColumn());
  EXPECT_EQ(4, to.getRow());
  EXPECT_EQ(4, to.getColumn());
}

TEST(MoveParserTest, RejectsEmptyInput) {
  MoveParser move_parser;
  const std::string input = "";

  const std::optional<Move> result = move_parser.parseMove(input);
  EXPECT_FALSE(result.has_value());
}

TEST(MoveParserTest, RejectsTooShortInput) {
  MoveParser move_parser;
  const std::string input = "e2e4";

  const std::optional<Move> result = move_parser.parseMove(input);
  EXPECT_FALSE(result.has_value());
}

TEST(MoveParserTest, RejectsInvalidSeparator) {
  MoveParser move_parser;
  const std::string input = "e2xe4";

  const std::optional<Move> result = move_parser.parseMove(input);
  EXPECT_FALSE(result.has_value());
}

TEST(MoveParserTest, DetectsInvalidFromCoordinate) {
  MoveParser move_parser;
  const std::string input = "i2 e4";

  const bool is_valid_from_coordinate = move_parser.hasValidFromCoordinate(input);

  EXPECT_FALSE(is_valid_from_coordinate);
}

TEST(MoveParserTest, DetectsInvalidToCoordinate) {
  MoveParser move_parser;
  const std::string input = "e2 i4";

  const bool is_valid_to_coordinate = move_parser.hasValidToCoordinate(input);

  EXPECT_FALSE(is_valid_to_coordinate);
}

TEST(MoveParserTest, ParsesBoundaryCoordinates) {
  MoveParser move_parser;
  const std::string input = "a1 h8";

  const std::optional<Move> result = move_parser.parseMove(input);
  ASSERT_TRUE(result.has_value());

  const Move &move = result.value();

  const Coordinate &from = move.getFrom();
  const Coordinate &to = move.getTo();

  EXPECT_EQ(7, from.getRow());
  EXPECT_EQ(0, from.getColumn());
  EXPECT_EQ(0, to.getRow());
  EXPECT_EQ(7, to.getColumn());
}

TEST(MoveParserTest, AcceptsSameSquareSyntax) {
  MoveParser move_parser;
  const std::string input = "e2 e2";

  const std::optional<Move> result = move_parser.parseMove(input);

  EXPECT_TRUE(result.has_value());
}