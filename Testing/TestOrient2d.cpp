#include "predicates.h"
#include "testing.h"

template <typename T, typename Comparator>
bool testOrient2d(const T& ax, const T& ay, const T& bx, const T& by, const T& cx, const T& cy,
  Comparator compFunc, const char* message)
{
  T pa[2] = { ax, ay };
  T pb[2] = { bx, by };
  T pc[2] = { cx, cy };
  bool result = compFunc(predicates::adaptive::orient2d(pa, pb, pc), 0);
  IS_TRUE(result, message);
  return result;
}

int main(int argc, char** argv)
{
  bool result = testOrient2d<double>(
    0, 0, 1, 1, 0, 1, [&](const double l, const double r) noexcept -> bool { return l > r; },
    "counterclockwise");
  result &= testOrient2d<double>(
    0, 0, 0.5, 0.5, 1, 1, [&](const double l, const double r) noexcept -> bool { return l == r; },
    "collinear");
  result &= testOrient2d<double>(
    0, 0, 0, 1, 1, 1, [&](const double l, const double r) noexcept -> bool { return l < r; },
    "clockwise");
  return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
