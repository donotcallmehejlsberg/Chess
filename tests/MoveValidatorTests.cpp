#include <gtest/gtest.h>

#include <array>

#include "Board/Board.hpp"
#include "Movement/MoveValidator.hpp"
#include "Pieces/Bishop.hpp"
#include "Pieces/King.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Queen.hpp"
#include "Pieces/Rook.hpp"

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

TEST(MoveValidatorTest, AcceptsRookMovesInAllStraightDirections) {
  Board board;
  MoveValidator move_validator;

  Rook white_rook(Color::White);
  const Coordinate from(4, 4);

  const std::array<Coordinate, 4> destinations = {
      Coordinate(4, 7),
      Coordinate(4, 0),
      Coordinate(7, 4),
      Coordinate(0, 4),
  };

  board.setPiece(from, &white_rook);

  for (const Coordinate &to : destinations) {
    const Move move(from, to);

    const bool is_valid =
        move_validator.isValidMove(board, move, Color::White, std::nullopt);

    EXPECT_TRUE(is_valid);
  }
}

TEST(MoveValidatorTest, RejectsDiagonalRookMove) {
  Board board;
  MoveValidator move_validator;
  Rook white_rook(Color::White);

  const Coordinate from(4, 4);
  const Coordinate to(6, 6);
  const Move move(from, to);

  board.setPiece(from, &white_rook);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, RejectsHorizontalRookMoveWhenPathIsBlocked) {
  Board board;
  MoveValidator move_validator;

  Rook white_rook(Color::White);
  Pawn blocking_pawn(Color::Black);

  const Coordinate from(4, 0);
  const Coordinate blocker(4, 3);
  const Coordinate to(4, 7);
  const Move move(from, to);

  board.setPiece(from, &white_rook);
  board.setPiece(blocker, &blocking_pawn);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, RejectsVerticalRookMoveWhenPathIsBlocked) {
  Board board;
  MoveValidator move_validator;

  Rook white_rook(Color::White);
  Pawn blocking_pawn(Color::Black);

  const Coordinate from(0, 4);
  const Coordinate blocker(3, 4);
  const Coordinate to(7, 4);
  const Move move(from, to);

  board.setPiece(from, &white_rook);
  board.setPiece(blocker, &blocking_pawn);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, AllowsRookToCaptureEnemyPiece) {
  Board board;
  MoveValidator move_validator;

  Rook white_rook(Color::White);
  Pawn black_pawn(Color::Black);

  const Coordinate from(4, 0);
  const Coordinate to(4, 7);
  const Move move(from, to);

  board.setPiece(from, &white_rook);
  board.setPiece(to, &black_pawn);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(MoveValidatorTest, AcceptsBishopMovesInAllDiagonalDirections) {
  Board board;
  MoveValidator move_validator;
  Bishop white_bishop(Color::White);

  const Coordinate from(4, 4);
  const std::array<Coordinate, 4> destinations = {
      Coordinate(7, 7),
      Coordinate(7, 1),
      Coordinate(1, 7),
      Coordinate(1, 1),
  };

  board.setPiece(from, &white_bishop);

  for (const Coordinate &to : destinations) {
    const Move move(from, to);

    const bool is_valid =
        move_validator.isValidMove(board, move, Color::White, std::nullopt);

    EXPECT_TRUE(is_valid);
  }
}

TEST(MoveValidatorTest, RejectsStraightBishopMove) {
  Board board;
  MoveValidator move_validator;
  Bishop white_bishop(Color::White);

  const Coordinate from(4, 4);
  const Coordinate to(4, 7);
  const Move move(from, to);

  board.setPiece(from, &white_bishop);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, RejectsBishopMoveWhenPathIsBlocked) {
  Board board;
  MoveValidator move_validator;

  Bishop white_bishop(Color::White);
  Pawn blocking_pawn(Color::Black);

  const Coordinate from(0, 0);
  const Coordinate blocker(2, 2);
  const Coordinate to(4, 4);
  const Move move(from, to);

  board.setPiece(from, &white_bishop);
  board.setPiece(blocker, &blocking_pawn);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, AcceptsHorizontalQueenMove) {
  Board board;
  MoveValidator move_validator;
  Queen white_queen(Color::White);

  const Coordinate from(4, 4);
  const Coordinate to(4, 7);
  const Move move(from, to);

  board.setPiece(from, &white_queen);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(MoveValidatorTest, AcceptsVerticalQueenMove) {
  Board board;
  MoveValidator move_validator;
  Queen white_queen(Color::White);

  const Coordinate from(4, 4);
  const Coordinate to(0, 4);
  const Move move(from, to);

  board.setPiece(from, &white_queen);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(MoveValidatorTest, AcceptsQueenMovesInAllDiagonalDirections) {
  Board board;
  MoveValidator move_validator;
  Queen white_queen(Color::White);

  const Coordinate from(4, 4);
  const std::array<Coordinate, 4> destinations = {
      Coordinate(7, 7),
      Coordinate(7, 1),
      Coordinate(1, 7),
      Coordinate(1, 1),
  };

  board.setPiece(from, &white_queen);

  for (const Coordinate &to : destinations) {
    const Move move(from, to);

    const bool is_valid =
        move_validator.isValidMove(board, move, Color::White, std::nullopt);

    EXPECT_TRUE(is_valid);
  }
}

TEST(MoveValidatorTest, RejectsInvalidQueenMoveGeometry) {
  Board board;
  MoveValidator move_validator;
  Queen white_queen(Color::White);

  const Coordinate from(4, 4);
  const Coordinate to(6, 5);
  const Move move(from, to);

  board.setPiece(from, &white_queen);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, RejectsQueenMoveWhenPathIsBlocked) {
  Board board;
  MoveValidator move_validator;

  Queen white_queen(Color::White);
  Pawn blocking_pawn(Color::Black);

  const Coordinate from(0, 0);
  const Coordinate blocker(2, 2);
  const Coordinate to(4, 4);
  const Move move(from, to);

  board.setPiece(from, &white_queen);
  board.setPiece(blocker, &blocking_pawn);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, AcceptsKingMoveByOneSquare) {
  Board board;
  MoveValidator move_validator;
  King white_king(Color::White);

  const Coordinate from(4, 4);
  const Coordinate to(5, 5);
  const Move move(from, to);

  board.setPiece(from, &white_king);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(MoveValidatorTest, RejectsKingMoveByMoreThanOneSquare) {
  Board board;
  MoveValidator move_validator;
  King white_king(Color::White);

  const Coordinate from(4, 4);
  const Coordinate to(6, 4);
  const Move move(from, to);

  board.setPiece(from, &white_king);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, RejectsKingMoveIntoCheck) {
  Board board;
  MoveValidator move_validator;

  King white_king(Color::White);
  Rook black_rook(Color::Black);

  const Coordinate from(4, 4);
  const Coordinate to(4, 5);
  const Coordinate black_rook_coordinate(0, 5);
  const Move move(from, to);

  board.setPiece(from, &white_king);
  board.setPiece(black_rook_coordinate, &black_rook);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, RejectsMoveThatLeavesKingInCheck) {
  Board board;
  MoveValidator move_validator;

  King white_king(Color::White);
  Rook white_rook(Color::White);
  Rook black_rook(Color::Black);

  const Coordinate king_coordinate(7, 4);
  const Coordinate rook_from(6, 4);
  const Coordinate rook_to(6, 5);
  const Coordinate black_rook_coordinate(0, 4);
  const Move move(rook_from, rook_to);

  board.setPiece(king_coordinate, &white_king);
  board.setPiece(rook_from, &white_rook);
  board.setPiece(black_rook_coordinate, &black_rook);

  ASSERT_FALSE(
      move_validator.getCheckedKingCoordinate(board, Color::White).has_value());

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(MoveValidatorTest, AcceptsKingMoveThatEscapesCheck) {
  Board board;
  MoveValidator move_validator;

  King white_king(Color::White);
  Rook black_rook(Color::Black);

  const Coordinate king_from(7, 4);
  const Coordinate king_to(7, 5);
  const Coordinate black_rook_coordinate(0, 4);
  const Move move(king_from, king_to);

  board.setPiece(king_from, &white_king);
  board.setPiece(black_rook_coordinate, &black_rook);

  ASSERT_TRUE(
      move_validator.getCheckedKingCoordinate(board, Color::White).has_value());

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(MoveValidatorTest, AcceptsMoveThatBlocksCheck) {
  Board board;
  MoveValidator move_validator;

  King white_king(Color::White);
  Rook white_rook(Color::White);
  Rook black_rook(Color::Black);

  const Coordinate king_coordinate(7, 4);
  const Coordinate rook_from(6, 3);
  const Coordinate rook_to(6, 4);
  const Coordinate black_rook_coordinate(0, 4);
  const Move move(rook_from, rook_to);

  board.setPiece(king_coordinate, &white_king);
  board.setPiece(rook_from, &white_rook);
  board.setPiece(black_rook_coordinate, &black_rook);

  ASSERT_TRUE(
      move_validator.getCheckedKingCoordinate(board, Color::White).has_value());

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_TRUE(is_valid);
}
