#include "Game/GameSetup.hpp"

void GameSetup::setupPieces(Board &board, Player &white_player,
                            Player &black_player) {
  if (white_player.getPlayerColor() == Color::White) {
    setupPawns(board, white_player, 6);
    setupBackRank(board, white_player, 7);
  }

  if (black_player.getPlayerColor() == Color::Black) {
    setupPawns(board, black_player, 1);
    setupBackRank(board, black_player, 0);
  }
}

void GameSetup::setupPawns(Board &board, Player &player, std::size_t row) {
  for (std::size_t column = 0; column < Board::SIZE; ++column) {
    auto pawn = std::make_unique<Pawn>(player.getPlayerColor());
    Piece *pawn_pointer = pawn.get();

    player.addPiece(std::move(pawn));
    board.setPiece(Coordinate(row, column), pawn_pointer);
  }
}

void GameSetup::setupBackRank(Board &board, Player &player, std::size_t row) {
  for (std::size_t column = 0; column < Board::SIZE; ++column) {
    std::unique_ptr<Piece> piece;

    if (column == 0 || column == 7) {
      piece = std::make_unique<Rook>(player.getPlayerColor());
    } else if (column == 1 || column == 6) {
      piece = std::make_unique<Knight>(player.getPlayerColor());
    } else if (column == 2 || column == 5) {
      piece = std::make_unique<Bishop>(player.getPlayerColor());
    } else if (column == 3) {
      piece = std::make_unique<Queen>(player.getPlayerColor());
    } else {
      piece = std::make_unique<King>(player.getPlayerColor());
    }

    Piece *piece_pointer = piece.get();
    player.addPiece(std::move(piece));
    board.setPiece(Coordinate(row, column), piece_pointer);
  }
}