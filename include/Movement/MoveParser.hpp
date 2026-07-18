#ifndef MOVE_PARSER_HPP
#define MOVE_PARSER_HPP

#include "InputReader.hpp"
#include "Movement/Move.hpp"

#include <optional>
#include <string>

class MoveParser {
public:
  std::optional<Move> MoveParser::handleMove(const std::string &input) const;

  bool isEmpty(const std::string &input) const;

  bool hasValidFromCoordinate(const std::string &input) const;
  bool hasValidToCoordinate(const std::string &input) const;
  bool hasValidLength(const std::string &input) const;
};

#endif