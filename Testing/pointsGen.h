#ifndef pointsGen_h__
#define pointsGen_h__

#include <vector>

#include "predicates.h"

#if (__cplusplus == 201103L || __cplusplus == 201703L || __cplusplus == 201703L ||                 \
  __cplusplus > 201703L)
#define CXX_RANDOM // better random number generation
#include <random>
#endif

//@brief : generate a random number in [0,1]
//@return: number in [0,1]
double rand01()
{
#ifdef CXX_RANDOM
  // prefer c++11 random number generation
  static std::random_device device;
  static const unsigned int seed = device();
  static std::mt19937 engine(seed);
  static std::uniform_real_distribution<double> dist(0.0, 1.0);
  return dist(engine);
#else
  // fall back to bad random numbers
  static bool once = true;
  if (once)
  {
    srand(time(NULL));
    once = false;
  }
  return static_cast<double>(rand()) / RAND_MAX;
#endif
}

template <typename T>
void generate(std::vector<T>& points)
{
  points.clear();
  points.resize(15);
  for (std::size_t i = 0; i < points.size(); i++)
    points[i] = static_cast<T>(rand01());
}
#endif // pointsGen_h__