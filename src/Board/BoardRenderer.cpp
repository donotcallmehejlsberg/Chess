#include "Board/BoardRenderer.hpp"

#include <iostream>
#include <string>

#include "Player.hpp"

namespace {

constexpr const char *ANSI_DARK_SQUARE_BACKGROUND = "\033[48;5;94m";
constexpr const char *ANSI_LIGHT_SQUARE_BACKGROUND = "\033[48;5;223m";

constexpr const char *ANSI_BLACK_PIECE_FOREGROUND = "\033[1;38;5;16m";
constexpr const char *ANSI_WHITE_PIECE_FOREGROUND = "\033[1;38;5;255m";

constexpr const char *ANSI_CHECK_SQUARE_BACKGROUND = "\033[48;5;124m";
constexpr const char *ANSI_LEGAL_MOVE_SQUARE_BACKGROUND = "\033[48;5;34m";

constexpr const char *ANSI_RESET = "\033[0m";

}  // namespace

void BoardRenderer::printBoard(const Board &board,
                               const Player &current_player) const {
  printBoard(board, current_player, std::nullopt, std::vector<Coordinate>{});
}

void BoardRenderer::printBoard(
    const Board &board, const Player &current_player,
    const std::optional<Coordinate> &checked_king_coordinate) const {
  printBoard(board, current_player, checked_king_coordinate,
             std::vector<Coordinate>{});
}

void BoardRenderer::printBoard(
    const Board &board, const Player &current_player,
    const std::optional<Coordinate> &checked_king_coordinate,
    const std::vector<Coordinate> &legal_move_coordinates) const {
  const Color color = current_player.getPlayerColor();

  if (color == Color::White) {
    for (std::size_t row = Board::SIZE; row > 0; row--) {
      std::cout << row << " ";
      for (std::size_t column = 0; column < Board::SIZE; column++) {
        Coordinate coordinate(Board::SIZE - row, column);
        const Square &square = board.getSquare(coordinate);
        printSquare(square, checked_king_coordinate, legal_move_coordinates);
        printPiece(square);
      }
      std::cout << std::endl;
    }

    printColumnLabels(color);
  }

  if (color == Color::Black) {
    for (std::size_t row = 0; row < Board::SIZE; row++) {
      std::cout << row + 1 << " ";
      for (std::size_t column = 0; column < Board::SIZE; column++) {
        Coordinate coordinate(Board::SIZE - row - 1, Board::SIZE - column - 1);
        const Square &square = board.getSquare(coordinate);
        printSquare(square, checked_king_coordinate, legal_move_coordinates);
        printPiece(square);
      }
      std::cout << std::endl;
    }

    printColumnLabels(color);
  }
  std::cout << std::endl;
}

void BoardRenderer::printColumnLabels(Color color) const {
  std::cout << "    ";

  if (color == Color::White) {
    for (char column = 'A'; column <= 'H'; column++) {
      std::cout << column;
      if (column != 'H') {
        std::cout << "   ";
      }
    }
  } else {
    for (char column = 'H'; column >= 'A'; column--) {
      std::cout << column;
      if (column != 'A') {
        std::cout << "   ";
      }
    }
  }

  std::cout << std::endl;
}

void BoardRenderer::printSquare(
    const Square &square,
    const std::optional<Coordinate> &checked_king_coordinate,
    const std::vector<Coordinate> &legal_move_coordinates) const {
  if (isCheckedKingSquare(square, checked_king_coordinate)) {
    std::cout << ANSI_CHECK_SQUARE_BACKGROUND;
    return;
  }

  if (isLegalMoveSquare(square, legal_move_coordinates)) {
    std::cout << ANSI_LEGAL_MOVE_SQUARE_BACKGROUND;
    return;
  }

  if (square.getSquareColor() == Color::White) {
    std::cout << ANSI_LIGHT_SQUARE_BACKGROUND;
  } else if (square.getSquareColor() == Color::Black) {
    std::cout << ANSI_DARK_SQUARE_BACKGROUND;
  }
}

void BoardRenderer::printPiece(const Square &square) const {
  const Piece *piece = square.getPiece();
  if (piece == nullptr) {
    std::cout << "    " << ANSI_RESET;
    return;
  }

  if (piece->getPieceColor() == Color::White) {
    std::cout << ANSI_WHITE_PIECE_FOREGROUND;
  } else {
    std::cout << ANSI_BLACK_PIECE_FOREGROUND;
  }

  std::cout << " " << piece->getSymbol() << "  " << ANSI_RESET;
}

bool BoardRenderer::isCheckedKingSquare(
    const Square &square,
    const std::optional<Coordinate> &checked_king_coordinate) const {
  if (!checked_king_coordinate.has_value()) {
    return false;
  }

  return square.getCoordinate().getRow() ==
             checked_king_coordinate.value().getRow() &&
         square.getCoordinate().getColumn() ==
             checked_king_coordinate.value().getColumn();
}

bool BoardRenderer::isLegalMoveSquare(
    const Square &square,
    const std::vector<Coordinate> &legal_move_coordinates) const {
  for (const Coordinate &coordinate : legal_move_coordinates) {
    if (square.getCoordinate().getRow() == coordinate.getRow() &&
        square.getCoordinate().getColumn() == coordinate.getColumn()) {
      return true;
    }
  }
  return false;
}
