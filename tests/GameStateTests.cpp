#include <gtest/gtest.h>

#include "Board/Board.hpp"
#include "Movement/MoveValidator.hpp"
#include "Pieces/Bishop.hpp"
#include "Pieces/King.hpp"
#include "Pieces/Queen.hpp"
#include "Pieces/Rook.hpp"

class GameStateTest : public ::testing::Test {
 protected:
  Board board;
  MoveValidator move_validator;

  King white_king{Color::White};
  King black_king{Color::Black};
  Queen white_queen{Color::White};
  Queen black_queen{Color::Black};
  Rook white_rook{Color::White};
  Bishop black_bishop{Color::Black};
};

TEST_F(GameStateTest, ReportsNoCheckWhenKingIsSafe) {
  const Coordinate king_coordinate(7, 4);

  board.setPiece(king_coordinate, &white_king);

  const std::optional<Coordinate> checked_king =
      move_validator.getCheckedKingCoordinate(board, Color::White);

  EXPECT_FALSE(checked_king.has_value());
}

TEST_F(GameStateTest, DetectsWhiteKingInCheck) {
  const Coordinate king_coordinate(7, 4);
  const Coordinate queen_coordinate(4, 4);

  board.setPiece(king_coordinate, &white_king);
  board.setPiece(queen_coordinate, &black_queen);

  const std::optional<Coordinate> checked_king =
      move_validator.getCheckedKingCoordinate(board, Color::White);

  EXPECT_TRUE(checked_king.has_value());
}

TEST_F(GameStateTest, DetectsBlackKingInCheck) {
  const Coordinate king_coordinate(0, 4);
  const Coordinate rook_coordinate(4, 4);

  board.setPiece(king_coordinate, &black_king);
  board.setPiece(rook_coordinate, &white_rook);

  const std::optional<Coordinate> checked_king =
      move_validator.getCheckedKingCoordinate(board, Color::Black);

  ASSERT_TRUE(checked_king.has_value());
  EXPECT_EQ(0, checked_king->getRow());
  EXPECT_EQ(4, checked_king->getColumn());
}

TEST_F(GameStateTest, FindsLegalMoveWhenOneExists) {
  board.setPiece(Coordinate(7, 4), &white_king);

  EXPECT_TRUE(move_validator.hasAnyLegalMove(board, Color::White));
}

TEST_F(GameStateTest, ReportsNoLegalMovesWhenEveryMoveIsBlocked) {
  board.setPiece(Coordinate(0, 0), &black_king);
  board.setPiece(Coordinate(1, 1), &white_queen);
  board.setPiece(Coordinate(2, 2), &white_king);

  EXPECT_FALSE(move_validator.hasAnyLegalMove(board, Color::Black));
}

TEST_F(GameStateTest, DetectsCheckmate) {
  board.setPiece(Coordinate(0, 0), &black_king);
  board.setPiece(Coordinate(1, 1), &white_queen);
  board.setPiece(Coordinate(2, 2), &white_king);

  ASSERT_TRUE(
      move_validator.getCheckedKingCoordinate(board, Color::Black).has_value());
  EXPECT_TRUE(move_validator.isCheckmate(board, Color::Black));
}

TEST_F(GameStateTest, RejectsCheckmateWhenKingCanEscape) {
  board.setPiece(Coordinate(0, 0), &black_king);
  board.setPiece(Coordinate(7, 0), &white_rook);

  ASSERT_TRUE(
      move_validator.getCheckedKingCoordinate(board, Color::Black).has_value());
  ASSERT_TRUE(move_validator.hasAnyLegalMove(board, Color::Black));

  EXPECT_FALSE(move_validator.isCheckmate(board, Color::Black));
}

TEST_F(GameStateTest, RejectsCheckmateWhenAnotherPieceCanBlockCheck) {
  const Coordinate bishop_from(0, 2);
  const Coordinate bishop_to(2, 4);
  const Move blocking_move(bishop_from, bishop_to);

  board.setPiece(Coordinate(0, 4), &black_king);
  board.setPiece(Coordinate(7, 4), &white_rook);
  board.setPiece(bishop_from, &black_bishop);

  ASSERT_TRUE(
      move_validator.getCheckedKingCoordinate(board, Color::Black).has_value());
  ASSERT_TRUE(move_validator.isValidMove(board, blocking_move, Color::Black,
                                         std::nullopt));

  EXPECT_FALSE(move_validator.isCheckmate(board, Color::Black));
}

TEST_F(GameStateTest, RejectsCheckmateWhenAttackingPieceCanBeCaptured) {
  const Coordinate king_coordinate(0, 4);
  const Coordinate rook_coordinate(1, 4);
  const Move capture_move(king_coordinate, rook_coordinate);

  board.setPiece(king_coordinate, &black_king);
  board.setPiece(rook_coordinate, &white_rook);

  ASSERT_TRUE(
      move_validator.getCheckedKingCoordinate(board, Color::Black).has_value());
  ASSERT_TRUE(move_validator.isValidMove(board, capture_move, Color::Black,
                                         std::nullopt));

  EXPECT_FALSE(move_validator.isCheckmate(board, Color::Black));
}

TEST_F(GameStateTest, DetectsStalemate) {
  board.setPiece(Coordinate(0, 0), &black_king);
  board.setPiece(Coordinate(2, 1), &white_queen);
  board.setPiece(Coordinate(2, 2), &white_king);

  ASSERT_FALSE(
      move_validator.getCheckedKingCoordinate(board, Color::Black).has_value());
  ASSERT_FALSE(move_validator.hasAnyLegalMove(board, Color::Black));

  EXPECT_TRUE(move_validator.isStalemate(board, Color::Black));
}

TEST_F(GameStateTest, RejectsStalemateWhenKingIsInCheck) {
  board.setPiece(Coordinate(0, 0), &black_king);
  board.setPiece(Coordinate(7, 0), &white_rook);

  ASSERT_TRUE(
      move_validator.getCheckedKingCoordinate(board, Color::Black).has_value());

  EXPECT_FALSE(move_validator.isStalemate(board, Color::Black));
}

TEST_F(GameStateTest, RejectsStalemateWhenLegalMoveExists) {
  board.setPiece(Coordinate(0, 0), &black_king);

  ASSERT_FALSE(
      move_validator.getCheckedKingCoordinate(board, Color::Black).has_value());
  ASSERT_TRUE(move_validator.hasAnyLegalMove(board, Color::Black));

  EXPECT_FALSE(move_validator.isStalemate(board, Color::Black));
}
