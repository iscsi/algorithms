#pragma once
#include <cmath>
#include <cstdlib>

namespace rili {
namespace test {
template <typename T1, typename T2, typename T3>
bool almostEqual(T1 x, T2 y, T3 precision) {
    return std::abs(x - y) <= std::abs(precision);
}
}  // namespace test
}  // namespace rili
