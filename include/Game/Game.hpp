#ifndef GAME_HPP
#define GAME_HPP

#include "Board/Board.hpp"
#include "Board/BoardRenderer.hpp"
#include "Color.hpp"
#include "Game/GameResult.hpp"
#include "Game/GameSetup.hpp"
#include "History/MoveHistory.hpp"
#include "Input/InputNormalizer.hpp"
#include "Input/InputReader.hpp"
#include "Movement/Move.hpp"
#include "Movement/MoveParser.hpp"
#include "Movement/MoveValidator.hpp"
#include "Player.hpp"

#include <memory>
#include <string>

class Game {
private:
  enum class CommandResult { NotCommand, Handled, GameEnded };
  using CommandHandler = CommandResult (Game::*)();

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

  MoveHistory move_history_;

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
  void printStatus() const;

  const Player &getCurrentPlayer() const;
  const Player &getOpponentPlayer() const;

  void switchPlayer();
  void setWinnerByOpponent();
  void handleCapture(const Move &move);

  bool handleInvalidInput() const;
  bool handleInvalidMove() const;
  void executeMove(const Move &move);
  void finishTurnAfterMove();

  CommandResult handleCommand(const std::string &input);
  CommandResult handleResign();
  CommandResult handleQuit();
  CommandResult handleBoard();
  CommandResult handleHelp();
  CommandResult handleRules();
  CommandResult handleCheck();
  CommandResult handleCaptured();
  CommandResult handleDrawOffer();
  CommandResult handleLegalMoves();
  CommandResult handleStatus();

  CommandResult handleHistory();

  void handlePromotion(const Move &move);
  std::unique_ptr<Piece> createPromotionPiece(Color color);
  bool canPromote(const Piece *piece, const Coordinate &coordinate) const;

  Player &getPlayerByColor(Color color);

  bool processMoveInput(const std::string &input);
  bool handleMainMenu();
  void handleTurn();

public:
  Game();
  void run();
};

#endif
