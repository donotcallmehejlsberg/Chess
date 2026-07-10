#include "Input/InputReader.hpp"

#include <iostream>

std::string InputReader::readLine() const
{
  std::string line; 
  std::getline(std::cin, line);

  return line;
}
