#include "pointsGen.h"

int main(int argc, char** argv)
{
  std::vector<double> points;
  generate(points);
  double x = predicates::adaptive::orient2d<double>(&points[0], &points[2], &points[4]);
  return EXIT_SUCCESS;
}
