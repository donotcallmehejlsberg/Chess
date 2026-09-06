#include "History/MoveHistory.hpp"

#include <optional>

void MoveHistory::addRecord(const MoveRecord &record) {
  records_.push_back(record);
}

bool MoveHistory::isEmpty() const { return records_.empty(); }

std::optional<MoveRecord> MoveHistory::getLastRecord() const {
  if (records_.empty()) {
    return std::nullopt;
  }
  return records_.back();
}

const std::vector<MoveRecord> &MoveHistory::getRecords() const {
  return records_;
}
