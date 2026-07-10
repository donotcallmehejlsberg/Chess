#include "Game/Game.hpp"

void Game::printResult() const
{
  if (result_ == GameResult::WhiteWon)
  {
    std::cout << "White won!" << std::endl;
  }
  else if (result_ == GameResult::BlackWon)
  {
    std::cout << "Black won!" << std::endl;
  }
  else if (result_ == GameResult::Draw)
  {
    std::cout << "Draw!" << std::endl;
  }
}

bool Game::isGameOver() const
{
  return result_ != GameResult::InProgress;
}

void Game::setupGame()
{
  setup_.setupPieces(board_, white_player_, black_player_);
  renderer_.printBoard(board_, white_player_);
}

void Game::run()
{
  setupGame();
  while(!isGameOver())
  {
    
  }
  printResult();
}



