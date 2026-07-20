#ifndef MOVE_VALIDATOR_HPP
#define MOVE_VALIDATOR_HPP

#include "Movement/Move.hpp"
#include "Board/Board.hpp"

class MoveValidator
{

public:
  bool isValidMove(const Board& board, const Move& move, Color color) const;

  bool isValidPawnMove() const; 

  bool isOccupiedByOwnPiece(const Board &board, const Coordinate &to, Color color) const;
  bool isOccupiedByEnemyPiece(const Board &board, const Coordinate &to, Color color) const;
  
  bool isMovingOwnPiece(const Piece *piece, Color color) const;
  bool isSameSquare(const Move &move) const;


};

#endif