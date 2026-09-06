#include "Game/GameView.hpp"

#include <iostream>

namespace {

constexpr const char *GREEN = "\033[1;32m";
constexpr const char *CYAN = "\033[1;36m";
constexpr const char *WHITE = "\033[1;37m";
constexpr const char *GRAY = "\033[90m";
constexpr const char *RESET = "\033[0m";

}  // namespace

void GameView::printWelcomeMessage() const {
  std::cout << '\n';

  std::cout << GREEN;

  std::cout << R"(
        ██████╗██╗  ██╗███████╗███████╗███████╗
       ██╔════╝██║  ██║██╔════╝██╔════╝██╔════╝▓
       ██║     ███████║█████╗  ███████╗███████╗▓
       ██║     ██╔══██║██╔══╝  ╚════██║╚════██║▓
       ╚██████╗██║  ██║███████╗███████║███████║▓
        ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝▓
)";

  std::cout << GRAY;
  std::cout << "          ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n";

  std::cout << RESET << '\n';

  std::cout << GREEN;
  std::cout << "              ╭────────────────────────────╮\n";
  std::cout << "              │";

  std::cout << WHITE;
  std::cout << "      ♔   C H E S S   ♚     ";

  std::cout << GREEN;
  std::cout << "│\n";

  std::cout << "              ╰────────────────────────────╯\n";

  std::cout << CYAN;
  std::cout << "                     READY TO PLAY\n";

  std::cout << RESET << "\n\n";
}

void GameView::printMainMenu() const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ── MAIN MENU ─────────────────────────────\n\n";

  std::cout << GREEN << "  > " << WHITE << "start" << GRAY
            << "      start a new game\n";

  std::cout << GREEN << "  > " << WHITE << "rules" << GRAY
            << "      show basic rules\n";

  std::cout << GREEN << "  > " << WHITE << "help" << GRAY
            << "       show available commands\n";

  std::cout << GREEN << "  > " << WHITE << "quit" << GRAY
            << "       exit the game\n";

  std::cout << GREEN;
  std::cout << "\n  ─────────────────────────────────────────\n";

  std::cout << GRAY;
  std::cout << "  Enter command\n";

  std::cout << GREEN << "  ❯ " << RESET;
}

void GameView::printTurnPrompt(Color color) const {
  const char *player = color == Color::White ? "WHITE" : "BLACK";

  const char *piece = color == Color::White ? "♔" : "♚";

  std::cout << GREEN << "  " << piece << "  " << WHITE << player << GREEN
            << "  ❯ " << RESET;
}

void GameView::printHelp() const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ── HELP / COMMANDS ──────────────────────\n\n";

  std::cout << GRAY;
  std::cout << "  MOVEMENT\n";

  std::cout << CYAN << "  > " << WHITE << "e2 e4" << GRAY
            << "       move a piece\n";

  std::cout << '\n';

  std::cout << GRAY;
  std::cout << "  GAME\n";

  std::cout << CYAN << "  > " << WHITE << "board" << GRAY
            << "       print the board\n";

  std::cout << CYAN << "  > " << WHITE << "moves" << GRAY
            << "       show legal moves\n";

  std::cout << CYAN << "  > " << WHITE << "check" << GRAY
            << "       show check status\n";

  std::cout << CYAN << "  > " << WHITE << "status" << GRAY
            << "      show game status\n";

  std::cout << CYAN << "  > " << WHITE << "history" << GRAY
            << "     show move history\n";

  std::cout << CYAN << "  > " << WHITE << "captured" << GRAY
            << "    show captured pieces\n";

  std::cout << '\n';

  std::cout << GRAY;
  std::cout << "  INFORMATION\n";

  std::cout << CYAN << "  > " << WHITE << "rules" << GRAY
            << "       show basic rules\n";

  std::cout << CYAN << "  > " << WHITE << "help" << GRAY
            << "        show this menu\n";

  std::cout << '\n';

  std::cout << GRAY;
  std::cout << "  GAME CONTROL\n";

  std::cout << CYAN << "  > " << WHITE << "draw" << GRAY
            << "        offer a draw\n";

  std::cout << CYAN << "  > " << WHITE << "resign" << GRAY
            << "      resign the game\n";

  std::cout << CYAN << "  > " << WHITE << "quit" << GRAY
            << "        exit the game\n";

  std::cout << GREEN;
  std::cout << "\n  ─────────────────────────────────────────\n";

  std::cout << RESET << '\n';
}

void GameView::printRules() const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ── CHESS RULES ──────────────────────────\n\n";

  std::cout << CYAN;
  std::cout << "  ◆ BASIC RULES\n\n";

  std::cout << GRAY << "    Move format      " << WHITE << "e2 e4\n";

  std::cout << GRAY << "    First move       " << WHITE << "White\n";

  std::cout << GRAY << "    Movement         " << WHITE
            << "Move only your own pieces\n";

  std::cout << GRAY << "    Own pieces       " << WHITE
            << "Cannot be captured\n";

  std::cout << GRAY << "    Capture          " << WHITE
            << "Move onto an opponent piece\n";

  std::cout << '\n';

  std::cout << CYAN;
  std::cout << "  ◆ PIECE MOVEMENT\n\n";

  std::cout << GREEN << "    PAWN    " << GRAY
            << "moves forward, captures diagonally\n";

  std::cout << GREEN << "    KNIGHT  " << GRAY
            << "moves in an L shape and can jump\n";

  std::cout << GREEN << "    ROOK    " << GRAY
            << "moves horizontally or vertically\n";

  std::cout << GREEN << "    BISHOP  " << GRAY << "moves diagonally\n";

  std::cout << GREEN << "    QUEEN   " << GRAY
            << "moves horizontally, vertically or diagonally\n";

  std::cout << GREEN << "    KING    " << GRAY
            << "moves one square in any direction\n";

  std::cout << '\n';

  std::cout << CYAN;
  std::cout << "  ◆ ENDING THE GAME\n\n";

  std::cout << GREEN << "    CHECKMATE\n";
  std::cout << GRAY << "      King is in check and has no legal move.\n\n";

  std::cout << GREEN << "    STALEMATE\n";
  std::cout << GRAY
            << "      Player has no legal move but is not in check.\n\n";

  std::cout << GREEN << "    DRAW\n";
  std::cout << GRAY << "      Both players agree to end without a winner.\n\n";

  std::cout << GREEN << "    RESIGN\n";
  std::cout << GRAY << "      One player gives up and the opponent wins.\n";

  std::cout << GREEN;
  std::cout << "\n  ─────────────────────────────────────────\n";

  std::cout << RESET << '\n';
}