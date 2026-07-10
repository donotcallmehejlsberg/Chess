#ifndef GAME_HPP
#define GAME_HPP

#include "Board/Board.hpp"
#include "Board/BoardRenderer.hpp"
#include "Color.hpp"
#include "Game/GameResult.hpp"
#include "Game/GameSetup.hpp"
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

  void printResult() const;
  bool isGameOver() const;
  void setupGame();

public:
  Game();
  void run();
};

#endif
