#include "Input/InputNormalizer.hpp"
#include <cctype>

std::string InputNormalizer::normalize(const std::string &input) const {
  std::string lower_input = input;

  for (char &character : lower_input) {
    character = static_cast<char>(std::tolower(character));
  }

  return lower_input;
}
