#include "Enum.hpp"

Direction getOpposite(const Direction& direction) {
	return Direction((direction + 2) % 4);
}