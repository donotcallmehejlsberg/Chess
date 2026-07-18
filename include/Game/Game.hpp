#ifndef GAME_HPP
#define GAME_HPP

#include "Board/Board.hpp"
#include "Board/BoardRenderer.hpp"
#include "Color.hpp"
#include "Game/GameResult.hpp"
#include "Game/GameSetup.hpp"
#include "Input/InputReader.hpp"
#include "Movement/Move.hpp"
#include "Movement/MoveParser.hpp"
#include "Movement/MoveValidator.hpp"
#include "Player.hpp"

class Game {
private:
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

  void printResult() const;
  bool isGameOver() const;
  void setupGame();

  void switchPlayer();
  void handleTurn();

public:
  Game();
  void run();
};

#endif
