
#include "Movement/Move.hpp"

Move::Move(Coordinate from, Coordinate to) : from_(from), to_(to) {}

const Coordinate &Move::getFrom() const { return from_; }
const Coordinate &Move::getTo() const { return to_; }