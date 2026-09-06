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

void GameView::printCapturedPieces(const Player &whitePlayer,
                                   const Player &blackPlayer) const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ── CAPTURED PIECES ──────────────────────\n\n";

  std::cout << CYAN << "  ♔ WHITE\n";
  std::cout << WHITE << "    ";
  whitePlayer.printCapturedPieces();
  std::cout << '\n';

  std::cout << CYAN << "  ♚ BLACK\n";
  std::cout << WHITE << "    ";
  blackPlayer.printCapturedPieces();
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "\n  ─────────────────────────────────────────\n";

  std::cout << RESET << '\n';
}

void GameView::printResult(GameResult result, const Player &player) const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ── GAME RESULT ──────────────────────────\n\n";

  if (result == GameResult::WhiteWon) {
    std::cout << WHITE << "  ♔  WHITE WINS\n";
    std::cout << GRAY << "     Checkmate. Game over.\n";

  } else if (result == GameResult::BlackWon) {
    std::cout << WHITE << "  ♚  BLACK WINS\n";
    std::cout << GRAY << "     Checkmate. Game over.\n";

  } else if (result == GameResult::Draw) {
    std::cout << CYAN << "  ◆  DRAW\n";
    std::cout << GRAY << "     The game ended without a winner.\n";

  } else if (result == GameResult::Quit) {
    std::cout << CYAN << "  ◆  GAME ENDED\n";
    std::cout << GRAY << "     " << player.getColorName()
              << " quit the game.\n";
  }

  std::cout << GREEN;
  std::cout << "\n  ─────────────────────────────────────────\n";

  std::cout << RESET << '\n';
}

void GameView::printCheckStatus(const Player &player, bool isInCheck) const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ── CHECK STATUS ─────────────────────────\n\n";

  if (isInCheck) {
    std::cout << CYAN << "  ◆ " << WHITE << player.getColorName() << GRAY
              << " is in check!\n";
  } else {
    std::cout << GREEN << "  ◆ " << WHITE << player.getColorName() << GRAY
              << " is not in check.\n";
  }

  std::cout << GREEN;
  std::cout << "\n  ─────────────────────────────────────────\n";

  std::cout << RESET << '\n';
}

void GameView::printStatus(const GameStatus &status, const Player &whitePlayer,
                           const Player &blackPlayer) const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ── GAME STATUS ──────────────────────────\n\n";

  std::cout << CYAN << "  ◆ CURRENT PLAYER\n";
  std::cout << WHITE << "    " << status.currentPlayerName << "\n\n";

  std::cout << CYAN << "  ◆ RESULT\n";
  std::cout << WHITE << "    ";

  if (status.result == GameResult::InProgress) {
    std::cout << "In progress";
  } else if (status.result == GameResult::WhiteWon) {
    std::cout << "White won";
  } else if (status.result == GameResult::BlackWon) {
    std::cout << "Black won";
  } else if (status.result == GameResult::Draw) {
    std::cout << "Draw";
  } else if (status.result == GameResult::Quit) {
    std::cout << "Quit";
  }

  std::cout << "\n\n";

  std::cout << CYAN << "  ◆ CHECK\n";
  std::cout << WHITE << "    " << (status.isInCheck ? "Yes" : "No") << "\n\n";

  std::cout << CYAN << "  ◆ SCORE\n";
  std::cout << WHITE << "    White: " << status.whiteScore << '\n'
            << "    Black: " << status.blackScore << '\n';

  printCapturedPieces(whitePlayer, blackPlayer);

  std::cout << RESET;
}

void GameView::printGameStartMessage() const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ── LET THE GAME BEGIN ───────────────────\n";

  std::cout << RESET << '\n';
}

void GameView::printGoodbye() const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ── GAME CLOSED ──────────────────────────\n\n";

  std::cout << WHITE;
  std::cout << "  Thanks for playing.\n";

  std::cout << GRAY;
  std::cout << "  See you on the board.\n";

  std::cout << GREEN;
  std::cout << "\n  ─────────────────────────────────────────\n";

  std::cout << RESET << '\n';
}

void GameView::printInvalidCommand() const {
  std::cout << GREEN << "  ! " << WHITE << "UNKNOWN COMMAND" << GRAY
            << "  Type 'help' to see available commands." << RESET << '\n';
}

void GameView::printQuitConfirmation(const Player &player) const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ── QUIT GAME ────────────────────────────\n\n";

  std::cout << WHITE << "  " << player.getColorName();
  std::cout << GRAY << ", quitting counts as resignation.\n\n";

  std::cout << CYAN << "  ◆ " << WHITE << "Are you sure? " << GRAY
            << "[yes/no]\n";

  std::cout << GREEN << "  ❯ " << RESET;
}

void GameView::printQuitConfirmed(const Player &player) const {
  std::cout << '\n';

  std::cout << GREEN << "  ◆ " << WHITE << player.getColorName() << GRAY
            << " left the game." << RESET << '\n';
}

void GameView::printQuitCancelled() const {
  std::cout << GREEN << "  ◆ " << WHITE << "Quit cancelled." << RESET << '\n';
}

void GameView::printResignation(const Player &player) const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ── RESIGNATION ──────────────────────────\n\n";

  std::cout << WHITE << "  " << player.getColorName() << GRAY
            << " resigned the game.\n";

  std::cout << GREEN;
  std::cout << "\n  ─────────────────────────────────────────\n";

  std::cout << RESET << '\n';
}

void GameView::printYesNoPrompt() const {
  std::cout << GREEN << "  ! " << GRAY << "Please enter " << WHITE << "yes"
            << GRAY << " or " << WHITE << "no" << GRAY << ".\n";

  std::cout << GREEN << "  ❯ " << RESET;
}

void GameView::printDrawOffer(const Player &currentPlayer,
                              const Player &opponentPlayer) const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ── DRAW OFFER ────────────────────────────\n\n";

  std::cout << WHITE << "  " << currentPlayer.getColorName() << GRAY
            << " offered a draw.\n";

  std::cout << WHITE << "  " << opponentPlayer.getColorName() << GRAY
            << ", accept the offer? " << WHITE << "[yes/no]\n\n";

  std::cout << GREEN << "  ❯ " << RESET;
}

void GameView::printDrawDeclined() const {
  std::cout << GREEN << "  ◆ " << WHITE << "Draw offer declined." << RESET
            << '\n';
}

void GameView::printLegalMovePrompt() const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ── LEGAL MOVES ──────────────────────────\n\n";

  std::cout << GRAY << "  Select a square " << WHITE << "(or 'cancel')\n";

  std::cout << GREEN << "  ❯ " << RESET;
}

void GameView::printNoPieceOnSquare() const {
  std::cout << GREEN << "  ! " << WHITE << "No piece on this square." << RESET
            << '\n';
}

void GameView::printChooseOwnPiece() const {
  std::cout << GREEN << "  ! " << WHITE << "Choose one of your own pieces."
            << RESET << '\n';
}

void GameView::printNoLegalMoves() const {
  std::cout << GREEN << "  ◆ " << WHITE << "This piece has no legal moves."
            << RESET << '\n';
}

void GameView::printCheckmate() const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ══ CHECKMATE ════════════════════════════\n\n";
  std::cout << WHITE;
  std::cout << "           ♚   G A M E   O V E R   ♔\n";
  std::cout << GREEN;
  std::cout << "\n  ═════════════════════════════════════════\n";

  std::cout << RESET << '\n';
}

void GameView::printStalemate() const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ══ STALEMATE ════════════════════════════\n\n";
  std::cout << CYAN << "  ◆ " << WHITE << "The game ends in a draw.\n";
  std::cout << GREEN;
  std::cout << "\n  ═════════════════════════════════════════\n";

  std::cout << RESET << '\n';
}

void GameView::printPromotionMenu() const {
  std::cout << '\n';

  std::cout << GREEN;
  std::cout << "  ── PAWN PROMOTION ───────────────────────\n\n";

  std::cout << CYAN;
  std::cout << "  ◆ CHOOSE YOUR PIECE\n\n";

  std::cout << GREEN << "  > " << WHITE << "q / queen" << GRAY
            << "      Queen\n";

  std::cout << GREEN << "  > " << WHITE << "r / rook" << GRAY
            << "       Rook\n";

  std::cout << GREEN << "  > " << WHITE << "b / bishop" << GRAY
            << "     Bishop\n";

  std::cout << GREEN << "  > " << WHITE << "n / knight" << GRAY
            << "     Knight\n";

  std::cout << GREEN;
  std::cout << "\n  ─────────────────────────────────────────\n";

  std::cout << GREEN << "  ❯ " << RESET;
}

void GameView::printPromotionResult(const Player &player,
                                    const std::string &pieceName) const {
  std::cout << '\n';
  std::cout << GREEN << "  ◆ " << WHITE << player.getColorName() << GRAY
            << " pawn promoted to " << CYAN << pieceName << GRAY << "!" << RESET
            << '\n';
}

void GameView::printInvalidPromotionChoice() const {
  std::cout << GREEN << "  ! " << WHITE << "INVALID PROMOTION CHOICE\n";
  std::cout << GRAY << "    Choose queen, rook, bishop, or knight." << RESET
            << '\n';
}

void GameView::printInvalidInput() const {
  std::cout << GREEN << "  ! " << WHITE << "INVALID INPUT" << RESET << '\n';
}

void GameView::printInvalidMove() const {
  std::cout << GREEN << "  ! " << WHITE << "INVALID MOVE" << RESET << '\n';
}