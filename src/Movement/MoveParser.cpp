#include "Movement/MoveParser.hpp"

std::optional<Move> MoveParser::handleMove(const std::string &input) {}

bool MoveParser::isEmpty(const std::string &input) const {
  return input.empty();
}

bool MoveParser::hasValidLength(const std::string &input) const {
  if (input.length() != 5) {
    return false;
  }
  return true;
}

bool MoveParser::hasValidFromCoordinate(const std::string &input) const {
  if (!hasValidLength(input)) {
    return false;
  }

  const char &file = input[0];
  const char &rank = input[1];

  if (file < 'a' || file > 'h') {
    return false;
  }
  if (rank < '1' || rank > '8') {
    return false;
  }
  return true;
}

bool MoveParser::hasValidToCoordinate(const std::string &input) const {
  if (!hasValidLength(input)) {
    return false;
  }

  const char &file = input[3];
  const char &rank = input[4];

  if (file < 'a' || file > 'h') {
    return false;
  }
  if (rank < '1' || rank > '8') {
    return false;
  }
  return true;
}
