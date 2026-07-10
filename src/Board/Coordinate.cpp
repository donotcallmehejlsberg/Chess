#include "Board/Coordinate.hpp"

Coordinate::Coordinate(std::size_t row, std::size_t column)
    : row_(row), column_(column) {}

std::size_t Coordinate::getRow() const { return row_; }

std::size_t Coordinate::getColumn() const { return column_; }
