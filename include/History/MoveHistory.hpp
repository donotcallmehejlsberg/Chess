#ifndef MOVE_HISTORY_HPP
#define MOVE_HISTORY_HPP

#include "History/MoveRecord.hpp"

#include <string>
#include <vector>

class MoveHistory {
private:
  std::vector<MoveRecord> records_;

  std::string coordinateToText(const Coordinate &coordinate) const;
  std::string pieceTypeToText(PieceType piece_type) const;
  void printRecord(const MoveRecord &record) const;

public:
  void addRecord(const MoveRecord &record);
  void printHistory() const;
  bool isEmpty() const;
  std::optional<MoveRecord> getLastRecord() const;
};

#endif
