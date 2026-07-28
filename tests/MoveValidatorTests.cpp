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

TEST(PawnMoveValidatorTest, AcceptsWhitePawnSingleStep) {
  Board board;
  MoveValidator move_validator;

  Pawn white_pawn(Color::White);
  const Coordinate pawn_from(4, 0);
  const Coordinate pawn_to(3, 0);

  const Move move(pawn_from, pawn_to);

  board.setPiece(pawn_from, &white_pawn);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(PawnMoveValidatorTest, AcceptsBlackPawnSingleStep) {
  Board board;
  MoveValidator move_validator;

  Pawn black_pawn(Color::Black);
  const Coordinate pawn_from(3, 0);
  const Coordinate pawn_to(4, 0);

  const Move move(pawn_from, pawn_to);

  board.setPiece(pawn_from, &black_pawn);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::Black, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(PawnMoveValidatorTest, AcceptsWhitePawnDoubleStepFromStartingRank) {
  Board board;
  MoveValidator move_validator;

  Pawn white_pawn(Color::White);
  const Coordinate pawn_from(6, 0);
  const Coordinate pawn_to(4, 0);

  const Move move(pawn_from, pawn_to);

  board.setPiece(pawn_from, &white_pawn);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(PawnMoveValidatorTest, AcceptsBlackPawnDoubleStepFromStartingRank) {
  Board board;
  MoveValidator move_validator;

  Pawn black_pawn(Color::Black);
  const Coordinate pawn_from(1, 0);
  const Coordinate pawn_to(3, 0);

  const Move move(pawn_from, pawn_to);

  board.setPiece(pawn_from, &black_pawn);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::Black, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(PawnMoveValidatorTest, RejectsPawnDoubleStepOutsideStartingRank) {
  Board board;
  MoveValidator move_validator;

  Pawn pawn(Color::White);
  const Coordinate pawn_from(5, 0);
  const Coordinate pawn_to(3, 0);

  const Move move(pawn_from, pawn_to);

  board.setPiece(pawn_from, &pawn);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(PawnMoveValidatorTest, RejectsPawnMoveWhenDestinationIsBlocked) {
  Board board;
  MoveValidator move_validator;

  Pawn white_pawn(Color::White);
  Rook black_rook(Color::Black);
  const Coordinate pawn_from(6, 0);
  const Coordinate pawn_to(4, 0);

  const Move move(pawn_from, pawn_to);

  board.setPiece(pawn_from, &white_pawn);
  board.setPiece(pawn_to, &black_rook);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(PawnMoveValidatorTest, RejectsPawnDoubleStepWhenMiddleSquareIsBlocked) {
  Board board;
  MoveValidator move_validator;

  Pawn white_pawn(Color::White);
  Rook black_rook(Color::Black);

  const Coordinate pawn_from(6, 0);
  const Coordinate pawn_to(4, 0);
  const Coordinate blocked_middle(5, 0);

  const Move move(pawn_from, pawn_to);

  board.setPiece(pawn_from, &white_pawn);
  board.setPiece(blocked_middle, &black_rook);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(PawnMoveValidatorTest, AllowsPawnToCaptureEnemyPieceDiagonally) {
  Board board;
  MoveValidator move_validator;

  Pawn white_pawn(Color::White);
  Rook black_rook(Color::Black);

  const Coordinate pawn_from(6, 0);
  const Coordinate pawn_to(5, 1);

  const Move move(pawn_from, pawn_to);

  board.setPiece(pawn_from, &white_pawn);
  board.setPiece(pawn_to, &black_rook);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(PawnMoveValidatorTest, RejectsPawnDiagonalMoveToEmptySquare) {
  Board board;
  MoveValidator move_validator;

  Pawn white_pawn(Color::White);

  const Coordinate pawn_from(6, 0);
  const Coordinate pawn_to(5, 1);

  const Move move(pawn_from, pawn_to);

  board.setPiece(pawn_from, &white_pawn);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(PawnMoveValidatorTest, RejectsPawnForwardCapture) {
  Board board;
  MoveValidator move_validator;

  Pawn white_pawn(Color::White);
  Rook black_rook(Color::Black);

  const Coordinate pawn_from(6, 0);
  const Coordinate pawn_to(5, 0);

  const Move move(pawn_from, pawn_to);

  board.setPiece(pawn_from, &white_pawn);
  board.setPiece(pawn_to, &black_rook);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(CastlingTest, AllowsWhiteKingsideCastling) {
  Board board;
  MoveValidator move_validator;

  King white_king(Color::White);
  Rook white_rook(Color::White);

  const Coordinate king_from(7, 4);
  const Coordinate king_to(7, 6);
  const Coordinate rook_coordinate(7, 7);
  const Move move(king_from, king_to);

  board.setPiece(king_from, &white_king);
  board.setPiece(rook_coordinate, &white_rook);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(CastlingTest, AllowsWhiteQueensideCastling) {
  Board board;
  MoveValidator move_validator;

  King white_king(Color::White);
  Rook white_rook(Color::White);

  const Coordinate king_from(7, 4);
  const Coordinate king_to(7, 2);
  const Coordinate rook_coordinate(7, 0);
  const Move move(king_from, king_to);

  board.setPiece(king_from, &white_king);
  board.setPiece(rook_coordinate, &white_rook);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(CastlingTest, AllowsBlackKingsideCastling) {
  Board board;
  MoveValidator move_validator;

  King black_king(Color::Black);
  Rook black_rook(Color::Black);

  const Coordinate king_from(0, 4);
  const Coordinate king_to(0, 6);
  const Coordinate rook_coordinate(0, 7);
  const Move move(king_from, king_to);

  board.setPiece(king_from, &black_king);
  board.setPiece(rook_coordinate, &black_rook);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::Black, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(CastlingTest, AllowsBlackQueensideCastling) {
  Board board;
  MoveValidator move_validator;

  King black_king(Color::Black);
  Rook black_rook(Color::Black);

  const Coordinate king_from(0, 4);
  const Coordinate king_to(0, 2);
  const Coordinate rook_coordinate(0, 0);
  const Move move(king_from, king_to);

  board.setPiece(king_from, &black_king);
  board.setPiece(rook_coordinate, &black_rook);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::Black, std::nullopt);

  EXPECT_TRUE(is_valid);
}

TEST(CastlingTest, RejectsCastlingWhenPathIsBlocked) {
  Board board;
  MoveValidator move_validator;

  King white_king(Color::White);
  Rook white_rook(Color::White);
  Bishop blocking_bishop(Color::White);

  const Coordinate king_from(7, 4);
  const Coordinate king_to(7, 6);
  const Coordinate rook_coordinate(7, 7);
  const Coordinate blocked_square(7, 5);
  const Move move(king_from, king_to);

  board.setPiece(king_from, &white_king);
  board.setPiece(rook_coordinate, &white_rook);
  board.setPiece(blocked_square, &blocking_bishop);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(CastlingTest, RejectsCastlingAfterKingHasMoved) {
  Board board;
  MoveValidator move_validator;

  King black_king(Color::Black);
  Rook black_rook(Color::Black);

  const Coordinate king_from(0, 4);
  const Coordinate king_to(0, 2);
  const Coordinate rook_coordinate(0, 0);
  const Move move(king_from, king_to);

  board.setPiece(king_from, &black_king);
  board.setPiece(rook_coordinate, &black_rook);

  black_king.markMoved();

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::Black, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(CastlingTest, RejectsCastlingAfterRookHasMoved) {
  Board board;
  MoveValidator move_validator;

  King black_king(Color::Black);
  Rook black_rook(Color::Black);

  const Coordinate king_from(0, 4);
  const Coordinate king_to(0, 2);
  const Coordinate rook_coordinate(0, 0);
  const Move move(king_from, king_to);

  board.setPiece(king_from, &black_king);
  board.setPiece(rook_coordinate, &black_rook);

  black_rook.markMoved();

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::Black, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(CastlingTest, RejectsCastlingWithoutRook) {
  Board board;
  MoveValidator move_validator;

  King black_king(Color::Black);

  const Coordinate king_from(0, 4);
  const Coordinate king_to(0, 2);
  const Move move(king_from, king_to);

  board.setPiece(king_from, &black_king);

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::Black, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(CastlingTest, RejectsCastlingWhileKingIsInCheck) {
  Board board;
  MoveValidator move_validator;

  King white_king(Color::White);
  Rook white_rook(Color::White);
  Queen black_queen(Color::Black);

  const Coordinate king_from(7, 4);
  const Coordinate king_to(7, 2);
  const Coordinate rook_coordinate(7, 0);
  const Coordinate queen_coordinate(0, 4);
  const Move move(king_from, king_to);

  board.setPiece(king_from, &white_king);
  board.setPiece(rook_coordinate, &white_rook);
  board.setPiece(queen_coordinate, &black_queen);

  ASSERT_TRUE(
      move_validator.getCheckedKingCoordinate(board, Color::White).has_value());

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(CastlingTest, RejectsCastlingThroughAttackedSquare) {
  Board board;
  MoveValidator move_validator;

  King white_king(Color::White);
  Rook white_rook(Color::White);
  Queen black_queen(Color::Black);

  const Coordinate king_from(7, 4);
  const Coordinate king_to(7, 2);
  const Coordinate rook_coordinate(7, 0);
  const Coordinate queen_coordinate(0, 3);
  const Move move(king_from, king_to);

  board.setPiece(king_from, &white_king);
  board.setPiece(rook_coordinate, &white_rook);
  board.setPiece(queen_coordinate, &black_queen);

  ASSERT_FALSE(
      move_validator.getCheckedKingCoordinate(board, Color::White).has_value());

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(CastlingTest, RejectsCastlingIntoCheck) {
  Board board;
  MoveValidator move_validator;

  King white_king(Color::White);
  Rook white_rook(Color::White);
  Queen black_queen(Color::Black);

  const Coordinate king_from(7, 4);
  const Coordinate king_to(7, 2);
  const Coordinate white_rook_coordinate(7, 0);
  const Coordinate black_queen_coordinate(0, 2);
  const Move move(king_from, king_to);

  board.setPiece(king_from, &white_king);
  board.setPiece(white_rook_coordinate, &white_rook);
  board.setPiece(black_queen_coordinate, &black_queen);

  ASSERT_FALSE(
      move_validator.getCheckedKingCoordinate(board, Color::White).has_value());

  const bool is_valid =
      move_validator.isValidMove(board, move, Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(EnPassantTest, AllowsWhiteEnPassantCapture) {
  Board board;
  MoveValidator move_validator;

  Pawn white_pawn(Color::White);
  Pawn black_pawn(Color::Black);

  const Coordinate white_pawn_from(3, 2);
  const Coordinate white_pawn_to(2, 3);

  const Coordinate black_pawn_from(1, 3);
  const Coordinate black_pawn_to(3, 3);

  board.setPiece(white_pawn_from, &white_pawn);
  board.setPiece(black_pawn_to, &black_pawn);

  const Move en_passant_move(white_pawn_from, white_pawn_to);
  const MoveRecord last_record(Color::Black, black_pawn_from, black_pawn_to,
                               PieceType::Pawn);

  const bool is_valid = move_validator.isValidMove(board, en_passant_move,
                                                   Color::White, last_record);

  EXPECT_TRUE(is_valid);
}

TEST(EnPassantTest, AllowsBlackEnPassantCapture) {
  Board board;
  MoveValidator move_validator;

  Pawn black_pawn(Color::Black);
  Pawn white_pawn(Color::White);

  const Coordinate black_pawn_from(4, 2);
  const Coordinate black_pawn_to(5, 3);

  const Coordinate white_pawn_from(6, 3);
  const Coordinate white_pawn_to(4, 3);

  board.setPiece(black_pawn_from, &black_pawn);
  board.setPiece(white_pawn_to, &white_pawn);

  const Move en_passant_move(black_pawn_from, black_pawn_to);

  const MoveRecord last_record(Color::White, white_pawn_from, white_pawn_to,
                               PieceType::Pawn);

  const bool is_valid = move_validator.isValidMove(board, en_passant_move,
                                                   Color::Black, last_record);

  EXPECT_TRUE(is_valid);
}

TEST(EnPassantTest, RejectsEnPassantWithoutPreviousMove) {
  Board board;
  MoveValidator move_validator;

  Pawn white_pawn(Color::White);
  Pawn black_pawn(Color::Black);

  const Coordinate white_pawn_from(3, 2);
  const Coordinate white_pawn_to(2, 3);
  const Coordinate black_pawn_coordinate(3, 3);

  board.setPiece(white_pawn_from, &white_pawn);
  board.setPiece(black_pawn_coordinate, &black_pawn);

  const Move en_passant_move(white_pawn_from, white_pawn_to);

  const bool is_valid = move_validator.isValidMove(board, en_passant_move,
                                                   Color::White, std::nullopt);

  EXPECT_FALSE(is_valid);
}

TEST(EnPassantTest, RejectsEnPassantWhenPreviousPieceWasNotPawn) {
  Board board;
  MoveValidator move_validator;

  Pawn white_pawn(Color::White);
  Rook black_rook(Color::Black);

  const Coordinate white_pawn_from(3, 2);
  const Coordinate white_pawn_to(2, 3);

  const Coordinate black_rook_from(1, 3);
  const Coordinate black_rook_to(3, 3);

  board.setPiece(white_pawn_from, &white_pawn);
  board.setPiece(black_rook_to, &black_rook);

  const Move en_passant_move(white_pawn_from, white_pawn_to);

  const MoveRecord last_record(Color::Black, black_rook_from, black_rook_to,
                               PieceType::Rook);

  const bool is_valid = move_validator.isValidMove(board, en_passant_move,
                                                   Color::White, last_record);

  EXPECT_FALSE(is_valid);
}

TEST(EnPassantTest, RejectsEnPassantAfterSinglePawnStep) {
  Board board;
  MoveValidator move_validator;

  Pawn white_pawn(Color::White);
  Pawn black_pawn(Color::Black);

  const Coordinate white_pawn_from(3, 2);
  const Coordinate white_pawn_to(2, 3);

  const Coordinate black_pawn_from(2, 3);
  const Coordinate black_pawn_to(3, 3);

  board.setPiece(white_pawn_from, &white_pawn);
  board.setPiece(black_pawn_to, &black_pawn);

  const Move en_passant_move(white_pawn_from, white_pawn_to);
  const MoveRecord last_record(Color::Black, black_pawn_from, black_pawn_to,
                               PieceType::Pawn);

  const bool is_valid = move_validator.isValidMove(board, en_passant_move,
                                                   Color::White, last_record);

  EXPECT_FALSE(is_valid);
}

TEST(EnPassantTest, RejectsEnPassantWhenEnemyPawnIsNotAdjacent) {
  Board board;
  MoveValidator move_validator;

  Pawn white_pawn(Color::White);
  Pawn black_pawn(Color::Black);

  const Coordinate white_pawn_from(3, 2);
  const Coordinate white_pawn_to(2, 3);

  const Coordinate black_pawn_from(1, 4);
  const Coordinate black_pawn_to(3, 4);

  board.setPiece(white_pawn_from, &white_pawn);
  board.setPiece(black_pawn_to, &black_pawn);

  const Move en_passant_move(white_pawn_from, white_pawn_to);
  const MoveRecord last_record(Color::Black, black_pawn_from, black_pawn_to,
                               PieceType::Pawn);

  const bool is_valid = move_validator.isValidMove(board, en_passant_move,
                                                   Color::White, last_record);

  EXPECT_FALSE(is_valid);
}

TEST(EnPassantTest, RejectsEnPassantAfterOwnPawnDoubleMove) {
  Board board;
  MoveValidator move_validator;

  Pawn white_pawn(Color::White);
  Pawn other_white_pawn(Color::White);

  const Coordinate white_pawn_from(4, 2);
  const Coordinate white_pawn_to(3, 3);

  const Coordinate other_pawn_from(6, 3);
  const Coordinate other_pawn_to(4, 3);

  board.setPiece(white_pawn_from, &white_pawn);
  board.setPiece(other_pawn_to, &other_white_pawn);

  const Move en_passant_move(white_pawn_from, white_pawn_to);
  const MoveRecord last_record(Color::White, other_pawn_from, other_pawn_to,
                               PieceType::Pawn);

  const bool is_valid = move_validator.isValidMove(board, en_passant_move,
                                                   Color::White, last_record);

  EXPECT_FALSE(is_valid);
}

TEST(EnPassantTest, RejectsEnPassantWhenItLeavesKingInCheck) {
  Board board;
  MoveValidator move_validator;

  Pawn white_pawn(Color::White);
  Pawn black_pawn(Color::Black);
  Queen black_queen(Color::Black);
  King white_king(Color::White);

  const Coordinate white_king_coordinate(3, 0);

  const Coordinate white_pawn_from(3, 2);
  const Coordinate white_pawn_to(2, 3);

  const Coordinate black_pawn_from(1, 3);
  const Coordinate black_pawn_to(3, 3);

  const Coordinate black_queen_coordinate(3, 7);

  board.setPiece(white_pawn_from, &white_pawn);
  board.setPiece(black_pawn_to, &black_pawn);
  board.setPiece(black_queen_coordinate, &black_queen);
  board.setPiece(white_king_coordinate, &white_king);

  const Move en_passant_move(white_pawn_from, white_pawn_to);
  const MoveRecord last_record(Color::Black, black_pawn_from, black_pawn_to,
                               PieceType::Pawn);

  ASSERT_FALSE(
      move_validator.getCheckedKingCoordinate(board, Color::White).has_value());

  const bool is_valid = move_validator.isValidMove(board, en_passant_move,
                                                   Color::White, last_record);

  EXPECT_FALSE(is_valid);
}
