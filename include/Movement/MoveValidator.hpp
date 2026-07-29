#ifndef MOVE_VALIDATOR_HPP
#define MOVE_VALIDATOR_HPP

#include <optional>
#include <vector>

#include "Board/Board.hpp"
#include "History/MoveRecord.hpp"
#include "Movement/Move.hpp"

class MoveValidator {
 public:
  // Validates a complete move against piece rules and king safety.
  bool isValidMove(const Board &board, const Move &move, Color color,
                   const std::optional<MoveRecord> &last_record) const;

  // Exposes special-move recognition needed when executing a valid move.
  bool isEnPassantMove(const Board &board, const Move &move, Color color,
                       const std::optional<MoveRecord> &last_record) const;
  bool isCastlingMove(const Board &board, const Move &move, Color color) const;

  // Queries legal moves and the current check or end-state conditions.
  std::optional<Coordinate> getCheckedKingCoordinate(const Board &board,
                                                     Color color) const;
  std::vector<Coordinate> getLegalMovesForPiece(const Board &board,
                                                const Coordinate &from,
                                                Color color) const;

  bool hasAnyLegalMove(const Board &board, Color color) const;
  bool isCheckmate(const Board &board, Color color) const;
  bool isStalemate(const Board &board, Color color) const;

 private:
  bool passesBasicMoveChecks(const Board &board, const Move &move, Color color,
                             const Piece *piece) const;
  // Checks shared move conditions and dispatches piece-specific rules.
  bool isPieceMovementValid(const Board &board, const Move &move,
                            Color color) const;
  bool isSameSquare(const Move &move) const;
  bool isMovingOwnPiece(const Piece *piece, Color color) const;
  bool isOccupiedByOwnPiece(const Board &board, const Coordinate &to,
                            Color color) const;
  bool isOccupiedByEnemyPiece(const Board &board, const Coordinate &to,
                              Color color) const;

  // Validates movement geometry for each standard chess piece.
  bool isValidPawnMove(const Board &board, const Move &move, Color color) const;
  bool isPawnOnStartingRank(const Piece *pawn, const Coordinate &from) const;
  bool isValidKnightMove(const Board &board, const Move &move,
                         Color color) const;
  bool isValidBishopMove(const Board &board, const Move &move,
                         Color color) const;
  bool isValidRookMove(const Board &board, const Move &move, Color color) const;
  bool isValidQueenMove(const Board &board, const Move &move,
                        Color color) const;
  bool isValidKingMove(const Board &board, const Move &move, Color color) const;
  bool isPathClear(const Board &board, const Move &move) const;

  // Finds the king and rejects moves that leave it on an attacked square.
  std::optional<Coordinate> findKingCoordinate(const Board &board,
                                               Color color) const;
  bool isKingInCheck(const Board &board, Color color) const;
  bool wouldLeaveKingInCheck(Board board, const Move &move, Color color) const;
  bool wouldLeaveKingInCheckAfterEnPassant(Board board, const Move &move,
                                           Color color,
                                           const MoveRecord &last_record) const;
  bool wouldPassThroughCheck(Board board, const Move &move, Color color) const;

  // Validates castling-specific geometry, path, and attack restrictions.
  bool isValidCastlingMove(const Board &board, const Move &move,
                           Color color) const;
  bool isCastlingPathClear(const Board &board, const Coordinate &king_from,
                           const Coordinate &rook_from) const;
};

#endif
