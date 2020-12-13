#ifndef testing_h__
#define testing_h__

#include <iostream>

// If parameter is not true, test fails
#define IS_TRUE(x, msg)                                                                            \
  {                                                                                                \
    if (!x)                                                                                        \
    {                                                                                              \
      std::cout << msg << ": " << __FUNCTION__ << " failed on line " << __LINE__ << std::endl;     \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
      std::cout << msg  << ": " << "Success" << std::endl;                                                \
    }                                                                                              \
  }

#endif // testing_h__
