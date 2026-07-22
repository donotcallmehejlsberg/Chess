#ifndef MOVE_VALIDATOR_HPP
#define MOVE_VALIDATOR_HPP

#include "Board/Board.hpp"
#include "Movement/Move.hpp"

#include <optional>

class MoveValidator {
private:
  bool isKingInCheck(const Board &board, Color color) const;
  std::optional<Coordinate> findKingCoordinate(const Board &board,
                                               Color color) const;
  bool isPieceMoveValid(const Board &board, const Move &move,
                        Color color) const;
  bool wouldLeaveKingInCheck(Board board, const Move &move,
                             Color color) const;

  bool isValidPawnMove(const Board &board, const Move &move, Color color) const;
  bool isPawnOnStartingRank(const Piece *pawn, const Coordinate &from) const;

  bool isValidKingMove(const Board &board, const Move &move, Color color) const;

  bool isValidKnightMove(const Board &board, const Move &move,
                         Color color) const;

  bool isValidRookMove(const Board &board, const Move &move, Color color) const;

  bool isValidBishopMove(const Board &board, const Move &move,
                         Color color) const;

  bool isValidQueenMove(const Board &board, const Move &move,
                        Color color) const;

  bool isPathClear(const Board &board, const Move &move) const;

  bool isOccupiedByOwnPiece(const Board &board, const Coordinate &to,
                            Color color) const;
  bool isOccupiedByEnemyPiece(const Board &board, const Coordinate &to,
                              Color color) const;

  bool isMovingOwnPiece(const Piece *piece, Color color) const;
  bool isSameSquare(const Move &move) const;
  

public:
  bool isValidMove(const Board &board, const Move &move, Color color) const;
  std::optional<Coordinate> getCheckedKingCoordinate(const Board &board,
                                                     Color color) const;
};

#endif
