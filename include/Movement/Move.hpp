#ifndef MOVE_HPP
#define MOVE_HPP

#include <iostream>

#include "Board/Coordinate.hpp"

class Move {
 private:
  Coordinate from_;
  Coordinate to_;

 public:
  Move(Coordinate from, Coordinate to);

  const Coordinate &getFrom() const;
  const Coordinate &getTo() const;
};

#endif
