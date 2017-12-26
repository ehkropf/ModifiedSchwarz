#ifndef UNITTEST_MOSW_H
#define UNITTEST_MOSW_H

#include "UnitTest++.h"

// Some handy macros for talkative unit tests.
#define TEST_OUT(S) std::cout << S << std::endl;
#define TEST_FILE(S) std::cout << "-----========== " << S << " ==========-----" << std::endl;
#define TEST_LINE(S) std::cout << "  --> " << S << " ... " << std::endl;
#define TEST_OK std::cout << "      OK" << std::endl;

#endif // UNITTEST_MOSW_H
