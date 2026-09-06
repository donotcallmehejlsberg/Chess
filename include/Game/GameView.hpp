#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <memory>
#include <string>

#include "Color.hpp"

class GameView {
 public:
  // Prints game messages, menus, rules, and status information.
  void printWelcomeMessage() const;
  void printMainMenu() const;
  void printHelp() const;
  void printRules() const;
  void printTurnPrompt(Color color) const;
};

#endif
