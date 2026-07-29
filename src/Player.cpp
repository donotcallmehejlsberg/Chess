#include "Player.hpp"

#include <iostream>

Player::Player(Color color) : color_(color), score_(INITIAL_SCORE) {}

Color Player::getPlayerColor() const { return color_; }

int Player::getScore() const { return score_; }

void Player::setScore(int score) { score_ = score; }

void Player::addPiece(std::unique_ptr<Piece> piece) {
  pieces_.push_back(std::move(piece));
}

void Player::addCapturedPiece(PieceType piece_type) {
  captured_pieces_.push_back(piece_type);
}

Piece *Player::promotePiece(const Piece *old_piece,
                            std::unique_ptr<Piece> new_piece) {
  if (old_piece == nullptr || new_piece == nullptr ||
      old_piece->getPieceType() != PieceType::Pawn) {
    return nullptr;
  }

  if (new_piece->getPieceColor() != old_piece->getPieceColor()) {
    return nullptr;
  }

  const PieceType new_type = new_piece->getPieceType();
  if (new_type == PieceType::King || new_type == PieceType::Pawn) {
    return nullptr;
  }

  for (auto &piece : pieces_) {
    if (piece.get() == old_piece) {
      piece = std::move(new_piece);
      return piece.get();
    }
  }
  return nullptr;
}

void Player::printCapturedPieces() const {
  if (captured_pieces_.empty()) {
    std::cout << "-";
    return;
  }
  for (const PieceType piece : captured_pieces_) {
    std::cout << pieceTypeToString(piece) << " ";
  }
}

std::string Player::getColorName() const {
  if (color_ == Color::White) {
    return "White";
  }

  if (color_ == Color::Black) {
    return "Black";
  }

  return "Unknown";
}
