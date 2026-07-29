#include <gtest/gtest.h>

#include <stdexcept>

#include "Board/Board.hpp"
#include "Movement/Move.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Rook.hpp"

TEST(BoardTest, IsEmptyInitially) {
  Board board;

  for (std::size_t row = 0; row < Board::SIZE; row++) {
    for (std::size_t column = 0; column < Board::SIZE; column++) {
      const Coordinate coordinate(row, column);

      EXPECT_FALSE(board.isOccupied(coordinate));
    }
  }
}

TEST(BoardTest, AcceptsValidCoordinates) {
  Board board;
  const Coordinate coordinate_1(0, 0);
  const Coordinate coordinate_2(7, 7);

  EXPECT_TRUE(board.isValidCoordinate(coordinate_1));
  EXPECT_TRUE(board.isValidCoordinate(coordinate_2));
}

TEST(BoardTest, RejectsInvalidCoordinates) {
  Board board;
  const Coordinate coordinate_3(8, 0);
  const Coordinate coordinate_4(0, 8);

  EXPECT_FALSE(board.isValidCoordinate(coordinate_3));
  EXPECT_FALSE(board.isValidCoordinate(coordinate_4));
}

TEST(BoardTest, ReturnsNullForInvalidPieceCoordinate) {
  const Board board;
  const Coordinate invalid_row(8, 0);
  const Coordinate invalid_column(0, 8);

  EXPECT_EQ(nullptr, board.getPiece(invalid_row));
  EXPECT_EQ(nullptr, board.getPiece(invalid_column));
}

TEST(BoardTest, IgnoresSetPieceAtInvalidCoordinate) {
  Board board;
  Rook rook(Color::White);
  const Coordinate invalid_coordinate(8, 0);

  board.setPiece(invalid_coordinate, &rook);

  EXPECT_EQ(nullptr, board.getPiece(invalid_coordinate));
}

TEST(BoardTest, ReturnsNullWhenRemovingInvalidCoordinate) {
  Board board;
  const Coordinate invalid_coordinate(8, 0);

  EXPECT_EQ(nullptr, board.removePiece(invalid_coordinate));
}

TEST(BoardTest, ReportsInvalidCoordinateAsUnoccupied) {
  const Board board;
  const Coordinate invalid_coordinate(8, 0);

  EXPECT_FALSE(board.isOccupied(invalid_coordinate));
}

TEST(BoardTest, ThrowsWhenGettingSquareAtInvalidCoordinate) {
  const Board board;
  const Coordinate invalid_coordinate(8, 0);

  EXPECT_THROW(board.getSquare(invalid_coordinate), std::out_of_range);
}

TEST(BoardTest, SetsAndGetsPiece) {
  Board board;
  Rook rook(Color::White);
  const Coordinate coordinate(0, 0);

  board.setPiece(coordinate, &rook);

  EXPECT_EQ(&rook, board.getPiece(coordinate));
}

TEST(BoardTest, DetectsOccupiedSquare) {
  Board board;
  Rook rook(Color::White);
  const Coordinate coordinate(0, 0);

  board.setPiece(coordinate, &rook);

  EXPECT_TRUE(board.isOccupied(coordinate));
}

TEST(BoardTest, RemovesPiece) {
  Board board;
  Rook rook(Color::White);
  const Coordinate coordinate(0, 0);
  board.setPiece(coordinate, &rook);

  Piece *removed_piece = board.removePiece(coordinate);

  EXPECT_EQ(&rook, removed_piece);
  EXPECT_EQ(nullptr, board.getPiece(coordinate));
}

TEST(BoardTest, ReturnsNullWhenRemovingFromEmptySquare) {
  Board board;
  const Coordinate coordinate(0, 0);

  Piece *removed_piece = board.removePiece(coordinate);

  EXPECT_EQ(nullptr, removed_piece);
}

TEST(BoardTest, MovesPieceBetweenSquares) {
  Board board;
  Rook rook(Color::White);
  const Coordinate coordinate(0, 0);
  const Coordinate from(0, 0);
  const Coordinate to(2, 0);

  Move move(from, to);

  board.setPiece(coordinate, &rook);
  board.movePiece(move);

  EXPECT_EQ(nullptr, board.getPiece(from));
  EXPECT_EQ(&rook, board.getPiece(to));
}

TEST(BoardTest, MarksPieceAsMoved) {
  Board board;
  Rook rook(Color::White);
  const Coordinate coordinate(0, 0);
  const Coordinate from(0, 0);
  const Coordinate to(2, 0);

  Move move(from, to);

  board.setPiece(coordinate, &rook);
  board.movePiece(move);

  EXPECT_TRUE(rook.hasMoved());
}

TEST(BoardTest, DoesNothingWhenMovingFromEmptySquare) {
  Board board;
  Rook rook(Color::White);

  const Coordinate rook_coordinate(0, 0);
  const Coordinate empty_from(1, 0);
  const Coordinate to(2, 0);

  board.setPiece(rook_coordinate, &rook);
  const Move move(empty_from, to);

  board.movePiece(move);

  EXPECT_EQ(&rook, board.getPiece(rook_coordinate));
  EXPECT_FALSE(board.isOccupied(empty_from));
  EXPECT_FALSE(board.isOccupied(to));
}

TEST(BoardTest, PreservesPieceWhenMoveDestinationIsInvalid) {
  Board board;
  Rook rook(Color::White);

  const Coordinate from(0, 0);
  const Coordinate invalid_to(8, 0);
  const Move move(from, invalid_to);

  board.setPiece(from, &rook);
  board.movePiece(move);

  EXPECT_EQ(&rook, board.getPiece(from));
  EXPECT_FALSE(rook.hasMoved());
}

TEST(BoardTest, ClearsAllPieces) {
  Board board;
  Rook rook(Color::White);
  Pawn pawn(Color::Black);

  board.setPiece(Coordinate(0, 0), &rook);
  board.setPiece(Coordinate(6, 4), &pawn);

  ASSERT_TRUE(board.isOccupied(Coordinate(0, 0)));
  ASSERT_TRUE(board.isOccupied(Coordinate(6, 4)));

  board.clear();

  for (std::size_t row = 0; row < Board::SIZE; row++) {
    for (std::size_t column = 0; column < Board::SIZE; column++) {
      const Coordinate coordinate(row, column);

      EXPECT_FALSE(board.isOccupied(coordinate));
    }
  }
}

TEST(BoardTest, ReturnsSquareWithCorrectCoordinate) {
  const Board board;
  const Coordinate first_coordinate(0, 0);
  const Coordinate second_coordinate(5, 5);

  const Square &first_square = board.getSquare(first_coordinate);
  const Square &second_square = board.getSquare(second_coordinate);

  EXPECT_EQ(0, first_square.getCoordinate().getRow());
  EXPECT_EQ(0, first_square.getCoordinate().getColumn());

  EXPECT_EQ(5, second_square.getCoordinate().getRow());
  EXPECT_EQ(5, second_square.getCoordinate().getColumn());
}
