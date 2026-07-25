#include "History/MoveHistory.hpp"

#include <iostream>

void MoveHistory::addMove(const std::string &move) {
  if (move.empty()) {
    return;
  }
  moves_.push_back(move);
}

void MoveHistory::printHistory() const {
  if (moves_.empty()) {
    std::cout << "No moves yet." << std::endl;
    return;
  }

  std::cout << "Move history:" << std::endl;

  for (std::size_t index = 0; index < moves_.size(); index++) {
    if (index % 2 == 0) {
      std::cout << index / 2 + 1 << ". ";
      std::cout << "White: " << moves_[index];
    } else {
      std::cout << "   Black: " << moves_[index] << std::endl;
    }
  }

  if (moves_.size() % 2 != 0) {
    std::cout << std::endl;
  }
}

bool MoveHistory::isEmpty() const { return moves_.empty(); }