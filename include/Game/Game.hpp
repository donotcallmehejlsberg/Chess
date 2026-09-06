#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <string>

#include "Board/Board.hpp"
#include "Board/BoardRenderer.hpp"
#include "Color.hpp"
#include "Game/GameResult.hpp"
#include "Game/GameSetup.hpp"
#include "Game/GameView.hpp"
#include "History/MoveHistory.hpp"
#include "Input/InputNormalizer.hpp"
#include "Input/InputReader.hpp"
#include "Movement/Move.hpp"
#include "Movement/MoveParser.hpp"
#include "Movement/MoveValidator.hpp"
#include "Player.hpp"

class Game {
 public:
  Game();
  void run();

 private:
  enum class CommandResult { NotCommand, Handled, GameEnded };
  using CommandHandler = CommandResult (Game::*)();

  // Stores the main game state and owned game objects.
  Board board_;
  Player white_player_;
  Player black_player_;

  Color current_player_color_;
  GameResult result_;

  GameSetup setup_;
  GameView view_;

  BoardRenderer renderer_;
  MoveValidator move_validator_;
  MoveParser move_parser_;
  InputReader input_reader_;
  InputNormalizer input_normalizer_;
  MoveHistory move_history_;

  // Controls the main game loop from menu to turn handling.
  bool handleMainMenu();
  void setupGame();
  void handleTurn();
  bool isGameOver() const;

  // Handles text commands entered by the player.
  CommandResult handleCommand(const std::string &input);
  CommandResult handleQuit();
  CommandResult handleResign();
  CommandResult handleDrawOffer();
  CommandResult handleBoard();
  CommandResult handleHelp();
  CommandResult handleRules();
  CommandResult handleCheck();
  CommandResult handleCaptured();
  CommandResult handleLegalMoves();
  CommandResult handleStatus();
  CommandResult handleHistory();

  // Executes a validated move and updates the game afterwards.
  bool processMoveInput(const std::string &input);
  std::optional<PieceType> executeMove(const Move &move);
  void finishTurnAfterMove();
  void handleCapture(const Move &move);
  void executeCastling(const Move &move);
  void handleEnPassantCapture(const Move &move);

  // Handles pawn promotion when a pawn reaches the last rank.
  std::optional<PieceType> handlePromotion(const Move &move);
  std::unique_ptr<Piece> createPromotionPiece(Color color);
  bool canPromote(const Piece *piece, const Coordinate &coordinate) const;

  // Finds players and updates whose turn or result it is.
  Player &getPlayerByColor(Color color);
  const Player &getCurrentPlayer() const;
  const Player &getOpponentPlayer() const;
  void switchPlayer();
  void setOpponentAsWinner();

  // Prints standard error messages for bad input or invalid moves.
  bool handleInvalidInput() const;
  bool handleInvalidMove() const;

  // Prints game messages, menus, rules, and status information.
  void printCheckStatus() const;
  void printStatus() const;
};

#endif
