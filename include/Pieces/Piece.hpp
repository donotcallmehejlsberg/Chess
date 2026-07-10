#ifndef PIECE_HPP
#define PIECE_HPP

#include "Color.hpp"
#include "PieceType.hpp"

#include <string>

class Piece {
private:
  Color color_;
  PieceType piece_type_;

public:
  Piece(Color color, PieceType piece_type);

  virtual ~Piece() = default;
  Piece(const Piece &other) = delete;
  Piece &operator=(const Piece &other) = delete;

  Color getPieceColor() const;
  PieceType getPieceType() const;
  std::string getSymbol() const;

  int getValue() const;
};

#endif
