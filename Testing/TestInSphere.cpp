#include "pointsGen.h"

int main(int argc, char** argv)
{
  std::vector<double> points;
  generate(points);
  double x = predicates::adaptive::insphere<double>(
    &points[0], &points[3], &points[6], &points[9], &points[12]);
  return EXIT_SUCCESS;
}