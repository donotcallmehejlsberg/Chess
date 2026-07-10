#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <cstddef>

class Coordinate {
private:
  std::size_t row_;
  std::size_t column_;

public:
  Coordinate(std::size_t row, std::size_t column);

  std::size_t getRow() const;
  std::size_t getColumn() const;
};

#endif
