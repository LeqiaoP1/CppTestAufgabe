#include "CPgmAverager.hpp"

#include "gtest/gtest.h"
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

TEST(UT_PgmAverager, dummy) 
{
    std::cout << "current path is: " << fs::current_path() << std::endl;
    bool res = true;
    ASSERT_TRUE(res);
}

// negative test for catching exception if no source .pgm ever added for averaging
TEST(UT_PgmAverager, produceWithoutAnyPgmSource) 
{
    TestAufgabe::CPgmAverager pgmAverager;
    try {
        pgmAverager.produce(std::string{"./data/average.pgm"});
        FAIL() << "Expected std::logic_error";
    } catch(std::logic_error const &ex) {
        ASSERT_EQ(ex.what(), std::string("Not initialized"));
    }
}

// negative test for catching exeception if different size in pgm files
TEST(UT_PgmAverager, produceWithTwoPgmSourceButDifferentSize) 
{
    TestAufgabe::CPgmAverager pgmAverager;
    try {
        pgmAverager.addSource(std::string{"./data/a.pgm"});
        pgmAverager.addSource(std::string{"./data/b.pgm"});
        pgmAverager.produce(std::string{"./data/average2.pgm"});
        FAIL() << "Expected std::logic_error";
    } catch(std::runtime_error const &ex) {
        ASSERT_EQ(ex.what(), std::string("Parse input pgm file ./data/b.pgm failed"));
    }
}


TEST(UT_PgmAverager, produceWithOnePgmSource) 
{
    TestAufgabe::CPgmAverager pgmAverager;
    try {
        pgmAverager.addSource(std::string{"./data/a.pgm"});
        pgmAverager.produce(std::string{"./data/case1_average.pgm"});
    } catch(std::exception const &ex) {
        FAIL() << "unexpected exception " << ex.what();
    }
}


TEST(UT_PgmAverager, produceWithTwoPgmSource) 
{
    TestAufgabe::CPgmAverager pgmAverager;
    try {
        pgmAverager.addSource(std::string{"./data/a.pgm"});
        pgmAverager.addSource(std::string{"./data/all0.pgm"});
        pgmAverager.produce(std::string{"./data/case2_average.pgm"});
    } catch(std::exception const &ex) {
        FAIL() << "unexpected exception " << ex.what();
    }
}
