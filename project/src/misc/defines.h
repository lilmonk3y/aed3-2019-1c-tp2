#ifndef DEFINES_H
#define DEFINES_H

#include <limits>

using ulong = unsigned long;
using uint = unsigned int;

const ulong infinity = std::numeric_limits<ulong>::max() / 2 - 1;
const ulong none = std::numeric_limits<ulong>::max();

#define TANK_CAPACITY 60
#define INITIAL_GAS_CHARGE 0
#define FINAL_GAS_CHARGE 0

#endif
