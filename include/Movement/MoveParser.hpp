#ifndef MOVE_PARSER_HPP
#define MOVE_PARSER_HPP

#include <cctype>
#include <optional>
#include <string>

#include "Input/InputReader.hpp"
#include "Movement/Move.hpp"

class MoveParser {
 public:
  std::optional<Move> parseMove(const std::string &input) const;
  std::optional<Coordinate> parseCoordinate(const std::string &input) const;

 private:
  bool isEmpty(const std::string &input) const;
  bool hasValidFromCoordinate(const std::string &input) const;
  bool hasValidToCoordinate(const std::string &input) const;
  bool hasValidLength(const std::string &input) const;
  bool hasValidSeparator(const std::string &input) const;
};

#endif
