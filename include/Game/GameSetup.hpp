#ifndef GAMESETUP_HPP
#define GAMESETUP_HPP

#include "Board/Board.hpp"

#include "Pieces/Bishop.hpp"
#include "Pieces/King.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Queen.hpp"
#include "Pieces/Rook.hpp"

#include "Pieces/Piece.hpp"

#include "Player.hpp"

#include <cstddef>
#include <memory>
#include <utility>

class GameSetup {
public:
  void setupPieces(Board &board, Player &white_player, Player &black_player);

  void setupPawns(Board &board, Player &player, std::size_t row);

  void setupBackRank(Board &board, Player &player, std::size_t row);
};

#endif
