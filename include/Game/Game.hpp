#ifndef GAME_HPP
#define GAME_HPP

#include "Board/Board.hpp"
#include "Board/BoardRenderer.hpp"
#include "Color.hpp"
#include "Game/GameResult.hpp"
#include "Game/GameSetup.hpp"
#include "Input/InputNormalizer.hpp"
#include "Input/InputReader.hpp"
#include "Movement/Move.hpp"
#include "Movement/MoveParser.hpp"
#include "Movement/MoveValidator.hpp"
#include "Player.hpp"

#include <string>

class Game {
private:
  enum class CommandResult { NotCommand, Handled, Quit };

  Board board_;

  Player white_player_;
  Player black_player_;

  Color current_player_color_;
  GameResult result_;

  GameSetup setup_;
  BoardRenderer renderer_;
  MoveValidator move_validator_;
  MoveParser move_parser_;
  InputReader input_reader_;
  InputNormalizer input_normalizer_;

  bool isGameOver() const;
  void setupGame();

  void printResult() const;
  void printWelcomeMessage() const;
  void printTurnPrompt(Color color) const;
  void printCheckStatus() const;
  void printHelp() const;
  void printRules() const;
  void printMainMenu() const;
  void printCapturedPieces() const;

  const Player &getCurrentPlayer() const;
  void switchPlayer();
  
  void handleCapture(const Move &move);
  CommandResult handleCommand(const std::string &input);
  bool processMoveInput(const std::string &input);
  bool handleMainMenu();
  void handleTurn();

public:
  Game();
  void run();
};

#endif
