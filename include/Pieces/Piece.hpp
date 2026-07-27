#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>

#include "Color.hpp"
#include "PieceType.hpp"

class Piece {
 private:
  Color color_;
  PieceType piece_type_;
  bool has_moved_;

 public:
  Piece(Color color, PieceType piece_type);

  virtual ~Piece() = default;
  Piece(const Piece &other) = delete;
  Piece &operator=(const Piece &other) = delete;

  Color getPieceColor() const;
  PieceType getPieceType() const;
  std::string getSymbol() const;

  bool hasMoved() const;
  void markMoved();

  int getValue() const;
};

#endif
