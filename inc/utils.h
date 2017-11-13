#include <iostream>

#ifdef ENABLE_DEBUG_MACRO
#   define DEBUG(x) x
#   define DEBUG_PRINT(x) std::cout<< "\033[1;31m[Debug]\033[0;33m " << x <<"\033[0m"
#else
#   define DEBUG(x)
#   define DEBUG_PRINT(x)
#endif

