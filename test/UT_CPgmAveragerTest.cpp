#include "CPgmAverager.hpp"

#include "gtest/gtest.h"
#include <stdexcept>

TEST(UT_PgmAverage, dummy) 
{
    bool res = true;
    ASSERT_TRUE(res);
}

TEST(UT_PgmAverage, init) 
{
    TestAufgabe::CPgmAverager pgmAverager;
    try {
        pgmAverager.produce(std::string{"./average.pgm"});
        FAIL() << "Expected std::logic_error";
    } catch(std::logic_error const &ex) {
        EXPECT_EQ(ex.what(), std::string("Not initialized"));
    }
}
