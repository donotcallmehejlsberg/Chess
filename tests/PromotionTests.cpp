#include <gtest/gtest.h>

#include <memory>

#include "Pieces/Bishop.hpp"
#include "Pieces/King.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Queen.hpp"
#include "Pieces/Rook.hpp"
#include "Player.hpp"

class PromotionTest : public ::testing::Test {
 protected:
  Player white_player{Color::White};
  Player black_player{Color::Black};

  std::unique_ptr<Pawn> pawn = std::make_unique<Pawn>(Color::White);
  Piece *old_pawn = pawn.get();
};

TEST_F(PromotionTest, PromotesOwnedPawnToQueen) {
  white_player.addPiece(std::move(pawn));

  Piece *promoted_piece = white_player.promotePiece(
      old_pawn, std::make_unique<Queen>(Color::White));

  ASSERT_NE(nullptr, promoted_piece);

  EXPECT_EQ(PieceType::Queen, promoted_piece->getPieceType());
  EXPECT_EQ(Color::White, promoted_piece->getPieceColor());
}

TEST_F(PromotionTest, PromotesOwnedPawnToRook) {
  white_player.addPiece(std::move(pawn));

  Piece *promoted_piece =
      white_player.promotePiece(old_pawn, std::make_unique<Rook>(Color::White));

  ASSERT_NE(nullptr, promoted_piece);
  EXPECT_EQ(PieceType::Rook, promoted_piece->getPieceType());
  EXPECT_EQ(Color::White, promoted_piece->getPieceColor());
}

TEST_F(PromotionTest, PromotesOwnedPawnToBishop) {
  white_player.addPiece(std::move(pawn));

  Piece *promoted_piece = white_player.promotePiece(
      old_pawn, std::make_unique<Bishop>(Color::White));

  ASSERT_NE(nullptr, promoted_piece);
  EXPECT_EQ(PieceType::Bishop, promoted_piece->getPieceType());
  EXPECT_EQ(Color::White, promoted_piece->getPieceColor());
}

TEST_F(PromotionTest, PromotesOwnedPawnToKnight) {
  white_player.addPiece(std::move(pawn));

  Piece *promoted_piece = white_player.promotePiece(
      old_pawn, std::make_unique<Knight>(Color::White));

  ASSERT_NE(nullptr, promoted_piece);
  EXPECT_EQ(PieceType::Knight, promoted_piece->getPieceType());
  EXPECT_EQ(Color::White, promoted_piece->getPieceColor());
}

TEST_F(PromotionTest, PromotesBlackPawnToBlackQueen) {
  std::unique_ptr<Pawn> black_pawn = std::make_unique<Pawn>(Color::Black);

  Piece *old_black_pawn = black_pawn.get();
  black_player.addPiece(std::move(black_pawn));

  Piece *promoted_piece = black_player.promotePiece(
      old_black_pawn, std::make_unique<Queen>(Color::Black));

  ASSERT_NE(nullptr, promoted_piece);
  EXPECT_EQ(PieceType::Queen, promoted_piece->getPieceType());
  EXPECT_EQ(Color::Black, promoted_piece->getPieceColor());
}

TEST_F(PromotionTest, RejectsNullOldPiece) {
  Piece *promoted_piece =
      white_player.promotePiece(nullptr, std::make_unique<Queen>(Color::White));

  EXPECT_EQ(nullptr, promoted_piece);
}

TEST_F(PromotionTest, RejectsNullNewPiece) {
  white_player.addPiece(std::move(pawn));

  Piece *promoted_piece = white_player.promotePiece(old_pawn, nullptr);

  EXPECT_EQ(nullptr, promoted_piece);
}

TEST_F(PromotionTest, RejectsNonPawnPiece) {
  std::unique_ptr<Rook> rook = std::make_unique<Rook>(Color::White);

  Rook *old_rook = rook.get();
  white_player.addPiece(std::move(rook));

  Piece *promoted_piece = white_player.promotePiece(
      old_rook, std::make_unique<Queen>(Color::White));

  EXPECT_EQ(nullptr, promoted_piece);
}

TEST_F(PromotionTest, RejectsPromotionToDifferentColor) {
  white_player.addPiece(std::move(pawn));

  Piece *promoted_piece = white_player.promotePiece(
      old_pawn, std::make_unique<Queen>(Color::Black));

  EXPECT_EQ(nullptr, promoted_piece);
}

TEST_F(PromotionTest, RejectsPromotionToKing) {
  white_player.addPiece(std::move(pawn));

  Piece *promoted_piece =
      white_player.promotePiece(old_pawn, std::make_unique<King>(Color::White));

  EXPECT_EQ(nullptr, promoted_piece);
}

TEST_F(PromotionTest, RejectsPromotionToPawn) {
  white_player.addPiece(std::move(pawn));

  Piece *promoted_piece =
      white_player.promotePiece(old_pawn, std::make_unique<Pawn>(Color::White));

  EXPECT_EQ(nullptr, promoted_piece);
}

TEST_F(PromotionTest, RejectsPawnNotOwnedByPlayer) {
  Piece *promoted_piece = white_player.promotePiece(
      old_pawn, std::make_unique<Queen>(Color::White));

  EXPECT_EQ(nullptr, promoted_piece);
}
