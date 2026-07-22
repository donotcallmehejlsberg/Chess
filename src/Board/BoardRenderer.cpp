#include "Board/BoardRenderer.hpp"
#include "Player.hpp"

#include <iostream>
#include <string>

namespace {
const std::string ANSI_DARK_SQUARE_BACKGROUND = "\033[48;5;94m";
const std::string ANSI_LIGHT_SQUARE_BACKGROUND = "\033[48;5;223m";

const std::string ANSI_BLACK_PIECE_FOREGROUND = "\033[1;38;5;16m";
const std::string ANSI_WHITE_PIECE_FOREGROUND = "\033[1;38;5;255m";

const std::string ANSI_CHECK_SQUARE_BACKGROUND = "\033[48;5;124m";

const std::string ANSI_RESET = "\033[0m";
} // namespace

void BoardRenderer::printBoard(const Board &board,
                               const Player &current_player) const {
  printBoard(board, current_player, std::nullopt);
}

void BoardRenderer::printBoard(
    const Board &board, const Player &current_player,
    const std::optional<Coordinate> &highlighted_coordinate) const {
  const Color color = current_player.getPlayerColor();

  if (color == Color::White) {
    for (std::size_t row = Board::SIZE; row > 0; row--) {
      std::cout << row << " ";
      for (std::size_t column = 0; column < Board::SIZE; column++) {
        Coordinate coordinate(Board::SIZE - row, column);
        const Square &square = board.getSquare(coordinate);
        printSquare(square, highlighted_coordinate);
        printPiece(square);
      }
      std::cout << std::endl;
    }

    std::cout << "    ";

    for (char column = 'A'; column <= 'H'; column++) {
      std::cout << column;
      if (column != 'H') {
        std::cout << "   ";
      }
    }
    std::cout << std::endl;
  }

  if (color == Color::Black) {
    for (std::size_t row = 0; row < Board::SIZE; row++) {
      std::cout << row + 1 << " ";
      for (std::size_t column = 0; column < Board::SIZE; column++) {
        Coordinate coordinate(Board::SIZE - row - 1, Board::SIZE - column - 1);
        const Square &square = board.getSquare(coordinate);
        printSquare(square, highlighted_coordinate);
        printPiece(square);
      }
      std::cout << std::endl;
    }

    std::cout << "    ";

    for (char column = 'H'; column >= 'A'; column--) {
      std::cout << column;
      if (column != 'A') {
        std::cout << "   ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void BoardRenderer::printSquare(
    const Square &square,
    const std::optional<Coordinate> &highlighted_coordinate) const {

  if (isHighlightedSquare(square, highlighted_coordinate)) {
    std::cout << ANSI_CHECK_SQUARE_BACKGROUND;
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

bool BoardRenderer::isHighlightedSquare(
    const Square &square,
    const std::optional<Coordinate> &highlighted_coordinate) const {
  if (!highlighted_coordinate.has_value()) {
    return false;
  }

  return square.getCoordinate().getRow() ==
             highlighted_coordinate.value().getRow() &&
         square.getCoordinate().getColumn() ==
             highlighted_coordinate.value().getColumn();
}
