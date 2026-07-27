#include "Movement/MoveParser.hpp"

std::optional<Move> MoveParser::parseMove(const std::string &input) const {
  if (isEmpty(input)) {
    return std::nullopt;
  }

  if (!hasValidLength(input)) {
    return std::nullopt;
  }

  if (!hasValidSeparator(input)) {
    return std::nullopt;
  }

  if (!hasValidFromCoordinate(input)) {
    return std::nullopt;
  }

  if (!hasValidToCoordinate(input)) {
    return std::nullopt;
  }

  const char &from_file = input[0];
  const char &from_rank = input[1];

  const char &to_file = input[3];
  const char &to_rank = input[4];

  const std::size_t from_column = static_cast<std::size_t>(from_file - 'a');
  const std::size_t from_row = static_cast<std::size_t>('8' - from_rank);

  const std::size_t to_column = static_cast<std::size_t>(to_file - 'a');
  const std::size_t to_row = static_cast<std::size_t>('8' - to_rank);

  Coordinate from(from_row, from_column);
  Coordinate to(to_row, to_column);

  return Move(from, to);
}

bool MoveParser::isEmpty(const std::string &input) const {
  return input.empty();
}

bool MoveParser::hasValidLength(const std::string &input) const {
  if (input.length() != 5) {
    return false;
  }
  return true;
}

bool MoveParser::hasValidSeparator(const std::string &input) const {
  if (input[2] != ' ') {
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

std::optional<Coordinate> MoveParser::parseCoordinate(
    const std::string &input) const {
  if (input.length() != 2) {
    return std::nullopt;
  }

  const char &file = input[0];
  const char &rank = input[1];

  if (file < 'a' || file > 'h') {
    return std::nullopt;
  }

  if (rank < '1' || rank > '8') {
    return std::nullopt;
  }

  const std::size_t column = static_cast<std::size_t>(file - 'a');
  const std::size_t row = static_cast<std::size_t>('8' - rank);

  return Coordinate(row, column);
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
