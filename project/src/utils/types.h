#ifndef TYPES_H
#define TYPES_H

#include <limits>

using ulong = unsigned long;
using uint = unsigned int;

const ulong infinity = std::numeric_limits<ulong>::max() / 2 - 1;
const ulong none = std::numeric_limits<ulong>::max();

#endif
