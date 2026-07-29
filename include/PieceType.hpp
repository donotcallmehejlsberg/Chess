#ifndef PIECE_TYPE_HPP
#define PIECE_TYPE_HPP

#include <string>

enum class PieceType { Pawn, Rook, Knight, Bishop, Queen, King };

std::string pieceTypeToString(PieceType piece_type);

#endif
