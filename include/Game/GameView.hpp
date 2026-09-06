#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <memory>
#include <string>

#include "Color.hpp"
#include "Game/GameResult.hpp"
#include "Player.hpp"

struct GameStatus {
  std::string currentPlayerName;
  GameResult result;
  bool isInCheck;
  int whiteScore;
  int blackScore;
};

class GameView {
 public:
  // Prints game messages, menus, rules, and status information.
  void printWelcomeMessage() const;
  void printMainMenu() const;
  void printHelp() const;
  void printRules() const;
  void printTurnPrompt(Color color) const;
  void printCapturedPieces(const Player &whitePlayer,
                           const Player &blackPlayer) const;

  void printResult(GameResult result, const Player &player) const;
  void printCheckStatus(const Player &player, bool isInCheck) const;
  void printStatus(const GameStatus &status, const Player &whitePlayer,
                   const Player &blackPlayer) const;
  void printGameStartMessage() const;
};

#endif
