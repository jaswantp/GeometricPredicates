#include "predicates.h"
#include "testing.h"

template <typename T, typename Comparator>
bool testInCircleExact(const T& ax, const T& ay, const T& bx, const T& by, const T& cx, const T& cy,
  const T& dx, const T& dy, Comparator compFunc, const char* message)
{
  T pa[2] = { ax, ay };
  T pb[2] = { bx, by };
  T pc[2] = { cx, cy };
  T pd[2] = { dx, dy };
  bool result = compFunc(predicates::exact::incircle(pa, pb, pc, pd), 0);
  IS_TRUE(result, message);
  return result;
}

template <typename T, typename Comparator>
bool testInCircleAdapt(const T& ax, const T& ay, const T& bx, const T& by, const T& cx, const T& cy,
  const T& dx, const T& dy, Comparator compFunc, const char* message)
{
  T pa[2] = { ax, ay };
  T pb[2] = { bx, by };
  T pc[2] = { cx, cy };
  T pd[2] = { dx, dy };
  bool result = compFunc(predicates::adaptive::incircle(pa, pb, pc, pd), 0);
  IS_TRUE(result, message);
  return result;
}

int main(int argc, char** argv)
{
  bool result = testInCircleExact<double>(
    0, -1, 1, 0, 0, 1, 0, 0,
    [&](const double l, const double r) noexcept -> bool { return l > r; }, "inside");
  result &= testInCircleExact<double>(
    0, -1, 1, 0, 0, 1, -0.5, 0,
    [&](const double l, const double r) noexcept -> bool { return l > r; }, "inside");
  result &= testInCircleExact<double>(
    0, -1, 1, 0, 0, 1, 0.5, 0,
    [&](const double l, const double r) noexcept -> bool { return l > r; }, "inside");

  result &= testInCircleExact<double>(
    0, -1, 1, 0, 0, 1, -1, 0,
    [&](const double l, const double r) noexcept -> bool { return l == r; }, "concyclic");
  result &= testInCircleExact<double>(
    0, -1, 1, 0, 0, 1, -1, 0,
    [&](const double l, const double r) noexcept -> bool { return l == r; }, "concyclic");

  result &= testInCircleExact<double>(
    0, -1, 1, 0, 0, 1, -1.5, 0,
    [&](const double l, const double r) noexcept -> bool { return l < r; }, "outside");
  result &= testInCircleExact<double>(
    0, -1, 1, 0, 0, 1, 1.5, 0,
    [&](const double l, const double r) noexcept -> bool { return l < r; }, "outside");

  result &= testInCircleAdapt<double>(
    0, -1, 1, 0, 0, 1, 0, 0, [&](const double l, const double r) noexcept -> bool { return l > r; },
    "inside");
  result &= testInCircleAdapt<double>(
    0, -1, 1, 0, 0, 1, -0.5, 0,
    [&](const double l, const double r) noexcept -> bool { return l > r; }, "inside");
  result &= testInCircleAdapt<double>(
    0, -1, 1, 0, 0, 1, 0.5, 0,
    [&](const double l, const double r) noexcept -> bool { return l > r; }, "inside");

  result &= testInCircleAdapt<double>(
    0, -1, 1, 0, 0, 1, -1, 0,
    [&](const double l, const double r) noexcept -> bool { return l == r; }, "concyclic");
  result &= testInCircleAdapt<double>(
    0, -1, 1, 0, 0, 1, -1, 0,
    [&](const double l, const double r) noexcept -> bool { return l == r; }, "concyclic");

  result &= testInCircleAdapt<double>(
    0, -1, 1, 0, 0, 1, -1.5, 0,
    [&](const double l, const double r) noexcept -> bool { return l < r; }, "outside");
  result &= testInCircleAdapt<double>(
    0, -1, 1, 0, 0, 1, 1.5, 0,
    [&](const double l, const double r) noexcept -> bool { return l < r; }, "outside");

  double x = 1e-64;
  for (int i = 0; i < 128 && result; ++i)
  {
    result &= testInCircleExact<double>(
      0, x, -x, -x, x, -x, 0, 0,
      [&](const double l, const double r) noexcept -> bool { return l > r; }, "inside");
    result &= testInCircleExact<double>(
      0, x, -x, -x, x, -x, 0, 2 * x,
      [&](const double l, const double r) noexcept -> bool { return l < r; }, "outside");
    result &= testInCircleExact<double>(
      0, x, -x, -x, x, -x, 0, x,
      [&](const double l, const double r) noexcept -> bool { return l == r; }, "concyclic");
    x *= 10;
  }

  return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
