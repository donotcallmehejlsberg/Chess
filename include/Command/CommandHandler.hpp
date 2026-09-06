#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <string>

#include "Board/Board.hpp"
#include "Board/BoardRenderer.hpp"
#include "Color.hpp"
#include "Command/CommandResult.hpp"
#include "Game/GameResult.hpp"
#include "Game/GameView.hpp"
#include "History/MoveHistory.hpp"
#include "Input/InputNormalizer.hpp"
#include "Input/InputReader.hpp"
#include "Movement/MoveParser.hpp"
#include "Movement/MoveValidator.hpp"
#include "Player.hpp"

class CommandHandler {
 public:
  CommandHandler(Board &board, Player &whitePlayer, Player &blackPlayer,
                 Color &currentPlayerColor, GameResult &result, GameView &view,
                 BoardRenderer &renderer, MoveValidator &moveValidator,
                 MoveParser &moveParser, InputReader &inputReader,
                 InputNormalizer &inputNormalizer, MoveHistory &moveHistory);

  CommandResult handleCommand(const std::string &input);

 private:
  using HandlerMethod = CommandResult (CommandHandler::*)();

  // Game owns these objects; CommandHandler only stores references to them.
  Board &board_;
  Player &white_player_;
  Player &black_player_;
  Color &current_player_color_;
  GameResult &result_;

  GameView &view_;
  BoardRenderer &renderer_;
  MoveValidator &move_validator_;
  MoveParser &move_parser_;
  InputReader &input_reader_;
  InputNormalizer &input_normalizer_;
  MoveHistory &move_history_;

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

  const Player &getCurrentPlayer() const;
  const Player &getOpponentPlayer() const;
  void setOpponentAsWinner();
  void printCheckStatus() const;
  void printStatus() const;
};

#endif
