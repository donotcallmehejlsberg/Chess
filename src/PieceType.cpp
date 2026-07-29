#include "PieceType.hpp"

std::string pieceTypeToString(PieceType piece_type) {
  switch (piece_type) {
    case PieceType::Pawn:
      return "Pawn";
    case PieceType::Rook:
      return "Rook";
    case PieceType::Knight:
      return "Knight";
    case PieceType::Bishop:
      return "Bishop";
    case PieceType::Queen:
      return "Queen";
    case PieceType::King:
      return "King";
  }

  return "Unknown";
}