#ifndef MOVE_HISTORY_HPP
#define MOVE_HISTORY_HPP

#include <optional>
#include <vector>

#include "History/MoveRecord.hpp"

class MoveHistory {
 private:
  std::vector<MoveRecord> records_;

 public:
  bool isEmpty() const;
  void addRecord(const MoveRecord &record);
  std::optional<MoveRecord> getLastRecord() const;
  const std::vector<MoveRecord> &getRecords() const;
};

#endif
