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

std::string Player::pieceTypeToString(PieceType piece_type) const {
  switch (piece_type) {
  case PieceType::Pawn:
    return "Pawn";
  case PieceType::Knight:
    return "Knight";
  case PieceType::Bishop:
    return "Bishop";
  case PieceType::Rook:
    return "Rook";
  case PieceType::Queen:
    return "Queen";
  case PieceType::King:
    return "King";
  }
  return "Unknown";
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