#include "predicates.h"
#include "testing.h"

template <typename T, typename Comparator>
bool testInSphereExact(const T& ax, const T& ay, const T& az, const T& bx, const T& by, const T& bz,
  const T& cx, const T& cy, const T& cz, const T& dx, const T& dy, const T& dz, const T& ex,
  const T& ey, const T& ez, Comparator compFunc, const char* message)
{
  T pa[3] = { ax, ay, az };
  T pb[3] = { bx, by, bz };
  T pc[3] = { cx, cy, cz };
  T pd[3] = { dx, dy, dz };
  T pe[3] = { ex, ey, ez };
  bool result = compFunc(predicates::exact::insphere(pa, pb, pc, pd, pe), 0);
  IS_TRUE(result, message);
  return result;
}

template <typename T, typename Comparator>
bool testInSphereAdaptive(const T& ax, const T& ay, const T& az, const T& bx, const T& by, const T& bz,
  const T& cx, const T& cy, const T& cz, const T& dx, const T& dy, const T& dz, const T& ex,
  const T& ey, const T& ez, Comparator compFunc, const char* message)
{
  T pa[3] = { ax, ay, az };
  T pb[3] = { bx, by, bz };
  T pc[3] = { cx, cy, cz };
  T pd[3] = { dx, dy, dz };
  T pe[3] = { ex, ey, ez };
  bool result = compFunc(predicates::adaptive::insphere(pa, pb, pc, pd, pe), 0);
  IS_TRUE(result, message);
  return result;
}

int main(int argc, char** argv)
{
  bool result = testInSphereExact<double>(
    1, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
    [&](const double l, const double r) noexcept -> bool { return l > r; }, "inside");
  result &= testInSphereExact<double>(
    1, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 2,
    [&](const double l, const double r) noexcept -> bool { return l < r; }, "outside");
  result &= testInSphereExact<double>(
    1, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 1, 0, 0, -1,
    [&](const double l, const double r) noexcept -> bool { return l == r; }, "cospherical");

  result &= testInSphereAdaptive<double>(
    1, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
    [&](const double l, const double r) noexcept -> bool { return l > r; }, "inside");
  result &= testInSphereAdaptive<double>(
    1, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 2,
    [&](const double l, const double r) noexcept -> bool { return l < r; }, "outside");
  result &= testInSphereAdaptive<double>(
    1, 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 1, 0, 0, -1,
    [&](const double l, const double r) noexcept -> bool { return l == r; }, "cospherical");
  return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
