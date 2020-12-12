#include "pointsGen.h"

int main(int argc, char** argv)
{
  std::vector<double> points;
  generate(points);
  double x = predicates::adaptive::incircle<double>(&points[0], &points[2], &points[4], &points[6]);
  return EXIT_SUCCESS;
}
