#include <gtest/gtest.h>

#include <array>

#include "Board/Board.hpp"
#include "Movement/MoveValidator.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/Pawn.hpp"

TEST(MoveValidatorTest, RejectsMoveFromEmptySquare) {
  Board board;
  MoveValidator move_validator;

  const Coordinate from(6, 4);
  const Coordinate to(4, 4);
  const Move move(from, to);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, RejectsMovingOpponentPiece) {
  Board board;
  MoveValidator move_validator;
  Knight black_knight(Color::Black);

  const Coordinate from(4, 4);
  const Coordinate to(2, 5);
  const Move move(from, to);

  board.setPiece(from, &black_knight);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, RejectsMoveToSameSquare) {
  Board board;
  MoveValidator move_validator;
  Knight white_knight(Color::White);

  const Coordinate from(4, 4);
  const Coordinate to(4, 4);
  const Move move(from, to);

  board.setPiece(from, &white_knight);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, RejectsMoveToSquareOccupiedByOwnPiece) {
  Board board;
  MoveValidator move_validator;

  Knight white_knight(Color::White);
  Pawn white_pawn(Color::White);

  const Coordinate from(4, 4);
  const Coordinate to(6, 3);
  const Move move(from, to);

  board.setPiece(from, &white_knight);
  board.setPiece(to, &white_pawn);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, AcceptsValidKnightMove) {
  Board board;
  MoveValidator move_validator;

  Knight white_knight(Color::White);

  const Coordinate from(4, 4);
  const Coordinate to(6, 3);
  const Move move(from, to);

  board.setPiece(from, &white_knight);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(MoveValidatorTest, RejectsInvalidKnightMove) {
  Board board;
  MoveValidator move_validator;

  Knight white_knight(Color::White);

  const Coordinate from(4, 4);
  const Coordinate to(7, 3);
  const Move move(from, to);

  board.setPiece(from, &white_knight);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, AcceptsKnightMovesInAllDirections) {
  Board board;
  MoveValidator move_validator;

  Knight white_knight(Color::White);
  const Coordinate from(4, 4);

  const std::array<Coordinate, 8> destinations = {
      Coordinate(6, 5), Coordinate(6, 3), Coordinate(2, 5), Coordinate(2, 3),
      Coordinate(5, 6), Coordinate(5, 2), Coordinate(3, 6), Coordinate(3, 2),
  };

  board.setPiece(from, &white_knight);

  for (const Coordinate &to : destinations) {
    const Move move(from, to);

    const bool is_valid =
        move_validator.isValidMove(board, move, Color::White, std::nullopt);

    EXPECT_TRUE(is_valid);
  }
}

TEST(MoveValidatorTest, AllowsKnightToCaptureEnemyPiece) {
  Board board;
  MoveValidator move_validator;

  Knight white_knight(Color::White);
  Pawn black_pawn(Color::Black);

  const Coordinate from(4, 4);
  const Coordinate to(6, 3);
  const Move move(from, to);

  board.setPiece(from, &white_knight);
  board.setPiece(to, &black_pawn);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(MoveValidatorTest, AllowsKnightToJumpOverPieces) {
  Board board;
  MoveValidator move_validator;

  Knight white_knight(Color::White);
  Pawn black_pawn(Color::Black);

  const Coordinate from(4, 4);
  const Coordinate to(6, 3);
  const Coordinate black_pawn_coord(5, 3);
  const Move move(from, to);

  board.setPiece(from, &white_knight);
  board.setPiece(black_pawn_coord, &black_pawn);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_TRUE(is_valid);
}
