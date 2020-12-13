#include "predicates.h"
#include "testing.h"

template <typename T, typename Comparator>
bool testOrient3d(const T& ax, const T& ay, const T& az, const T& bx, const T& by, const T& bz,
  const T& cx, const T& cy, const T& cz, const T& dx, const T& dy, const T& dz, Comparator compFunc,
  const char* message)
{
  T pa[3] = { ax, ay, az };
  T pb[3] = { bx, by, bz };
  T pc[3] = { cx, cy, cz };
  T pd[3] = { dx, dy, dz };
  bool result = compFunc(predicates::exact::orient3d(pa, pb, pc, pd), 0);
  IS_TRUE(result, message);
  return result;
}

int main(int argc, char** argv)
{
  bool result = testOrient3d<double>(
    0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1,
    [&](const double l, const double r) noexcept -> bool { return l > r; }, "above");
  result &= testOrient3d<double>(
    0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, -1,
    [&](const double l, const double r) noexcept -> bool { return l < r; }, "below");
  result &= testOrient3d<double>(
    0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
    [&](const double l, const double r) noexcept -> bool { return l == r; }, "coplanar");
  result &= testOrient3d<double>(
    0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, std::nextafter(0, 1),
    [&](const double l, const double r) noexcept -> bool { return l > r; }, "near above");
  result &= testOrient3d<double>(
    0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, std::nextafter(0, -1),
    [&](const double l, const double r) noexcept -> bool { return l < r; }, "near below");
  return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
