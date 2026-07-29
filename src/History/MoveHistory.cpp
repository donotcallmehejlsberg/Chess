#include "History/MoveHistory.hpp"

#include <iostream>
#include <optional>
#include <string>

#include "Color.hpp"
#include "PieceType.hpp"

std::string MoveHistory::coordinateToText(const Coordinate &coordinate) const {
  const char file = static_cast<char>('a' + coordinate.getColumn());
  const char rank = static_cast<char>('8' - coordinate.getRow());

  std::string text;
  text += file;
  text += rank;
  return text;
}

void MoveHistory::printRecord(const MoveRecord &record) const {
  if (record.getPlayerColor() == Color::White) {
    std::cout << "White: ";
  } else {
    std::cout << "Black: ";
  }

  std::cout << coordinateToText(record.getFrom()) << " "
            << coordinateToText(record.getTo());

  if (record.getCapturedPieceType().has_value()) {
    std::cout << " captured "
              << pieceTypeToString(record.getCapturedPieceType().value());
  }

  if (record.getPromotedPieceType().has_value()) {
    std::cout << " promoted to "
              << pieceTypeToString(record.getPromotedPieceType().value());
  }
}

void MoveHistory::addRecord(const MoveRecord &record) {
  records_.push_back(record);
}

void MoveHistory::printHistory() const {
  if (records_.empty()) {
    std::cout << "No moves yet." << std::endl;
    return;
  }

  std::cout << "Move history:" << std::endl;

  for (std::size_t index = 0; index < records_.size(); index++) {
    if (index % 2 == 0) {
      std::cout << index / 2 + 1 << ". ";
      printRecord(records_[index]);
    } else {
      std::cout << "   ";
      printRecord(records_[index]);
      std::cout << std::endl;
    }
  }

  if (records_.size() % 2 != 0) {
    std::cout << std::endl;
  }
}

bool MoveHistory::isEmpty() const { return records_.empty(); }

std::optional<MoveRecord> MoveHistory::getLastRecord() const {
  if (records_.empty()) {
    return std::nullopt;
  }
  return records_.back();
}
