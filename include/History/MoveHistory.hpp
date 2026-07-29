#ifndef MOVE_HISTORY_HPP
#define MOVE_HISTORY_HPP

#include <optional>
#include <string>
#include <vector>

#include "History/MoveRecord.hpp"

class MoveHistory {
 private:
  std::vector<MoveRecord> records_;

  std::string coordinateToText(const Coordinate &coordinate) const;
  void printRecord(const MoveRecord &record) const;

 public:
  void addRecord(const MoveRecord &record);
  void printHistory() const;
  bool isEmpty() const;
  std::optional<MoveRecord> getLastRecord() const;
};

#endif
