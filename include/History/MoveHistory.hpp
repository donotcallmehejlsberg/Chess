#ifndef MOVE_HISTORY_HPP
#define MOVE_HISTORY_HPP

#include <string>
#include <vector>

class MoveHistory {
private:
  std::vector<std::string> moves_;

public:
  void addMove(const std::string &move);
  void printHistory() const;
  bool isEmpty() const;
};

#endif
