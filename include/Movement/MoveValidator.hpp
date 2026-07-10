#ifndef MOVE_VALIDATOR_HPP
#define MOVE_VALIDATOR_HPP

#include "Movement/Move.hpp"
#include "Board/Board.hpp"

class MoveValidator
{

public:
  bool isValidMove(const Board& board, const Move& move, Color color) const; 
};

#endif