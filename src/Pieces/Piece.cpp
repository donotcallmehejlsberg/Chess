#include "Pieces/Piece.hpp"

Piece::Piece(Color color, PieceType piece_type)
    : color_(color), piece_type_(piece_type), has_moved_(false) {}

Color Piece::getPieceColor() const { return color_; }

PieceType Piece::getPieceType() const { return piece_type_; }

int Piece::getValue() const {
  switch (piece_type_) {
    case PieceType::Pawn:
      return 1;
    case PieceType::Knight:
    case PieceType::Bishop:
      return 3;
    case PieceType::Rook:
      return 5;
    case PieceType::Queen:
      return 9;
    case PieceType::King:
      return 0;
  }
  return 0;
}

std::string Piece::getSymbol() const {
  switch (piece_type_) {
    case PieceType::Pawn:
      return "♟";
    case PieceType::Knight:
      return "♞";
    case PieceType::Bishop:
      return "♝";
    case PieceType::Rook:
      return "♜";
    case PieceType::Queen:
      return "♛";
    case PieceType::King:
      return "♚";
  }
  return "";
}

bool Piece::hasMoved() const { return has_moved_; }

void Piece::markMoved() { has_moved_ = true; }
