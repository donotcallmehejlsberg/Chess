#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Color.hpp"
#include "Pieces/Piece.hpp"

#include <memory>
#include <string>
#include <vector>

static constexpr int INITIAL_SCORE = 0;

class Player {
private:
  Color color_;
  int score_;
  std::vector<std::unique_ptr<Piece>> pieces_;
  std::vector<PieceType> captured_pieces_;

public:
  Player(Color color);
  Player(const Player &other) = delete;
  Player &operator=(const Player &other) = delete;

  Color getPlayerColor() const;
  int getScore() const;
  void setScore(int score);

  void addPiece(std::unique_ptr<Piece> piece);
  void addCapturedPiece(PieceType piece_type);

  Piece *promotePiece(const Piece *old_piece, std::unique_ptr<Piece> new_piece);

  std::string pieceTypeToString(PieceType piece_type) const;
  void printCapturedPieces() const;

  std::string getColorName() const;
};

#endif
