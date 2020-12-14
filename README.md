# GeometricPredicates
[![Actions Status](https://github.com/jaswantp/GeometricPredicates/workflows/Build%20and%20Test/badge.svg)](https://github.com/jaswantp/GeometricPredicates/actions)

A C++ header-only library for *robust*/*exact* Geometric predicates based on [Jonathan Shewchuk's papers and c code](https://www.cs.cmu.edu/~quake/robust.html)

Refer to detailed [paper](https://www.cs.cmu.edu/afs/cs/project/quake/public/papers/robust-predicates.abstract) for notions of the terms *robust* and *exact*.

# Summary:
The orientation and incircle tests evaluate the sign of a matrix determinant.
As Schewchuck's [paper](https://www.cs.cmu.edu/afs/cs/project/quake/public/papers/robust-predicates.abstract) describes, a series of approximations to the determinant is computed until the accuracy of the *sign* is assured.

TLDR;

`predicates::adaptive::` when *slight* perturbations to input parameters *should* result in similar results. Use this almost always.

`predicates::exact::` when you prefer exact arithmetic. Very slow. Avoid this.

Predicates: 
 1. `incircle(pa, pb, pc, pd)`
 2. `insphere(pa, pb, pc, pd, pe)`
 3. `orient2d(pa, pb, pc)`
 4. `orient3d(pa, pb, pc, pd)`

# Consumption:
Ex: Within C++ project that uses `CMake >= 3.14`
```
### Root CMakeLists.txt for a project named 'fish'

add_library(fish ${FISH_SOURCES})

FetchContent_Declare(
	extern_GeometricPredicates

	GIT_REPOSITORY https://github.com/jaswantp/GeometricPredicates.git
	GIT_TAG	v1.0
)

FetchContent_MakeAvailable(extern_GeometricPredicates)

target_link_libraries(fish PRIVATE GeometricPredicates::GeometricPredicates)
```

`GP_BUILD_TESTS`: Build unit tests

`GP_BUILD_DEMO`:  Demo application
