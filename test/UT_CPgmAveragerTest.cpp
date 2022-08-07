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

// negative test for catching exeception
TEST(UT_PgmAverager, addPgmSourceFormatUnsupported) 
{
    TestAufgabe::CPgmAverager pgmAverager;
    try {
        pgmAverager.addSource(std::string{"./data/all0P1.pbm"});
        FAIL() << "Expected std::runtime_error";
    } catch(std::runtime_error const &ex) {
        ASSERT_EQ(ex.what(), std::string("Parse Pgm failed. Format not supported. ./data/all0P1.pbm"));
    }
}


// negative test for catching exeception
TEST(UT_PgmAverager, addTwoPgmSourceButDifferentSize) 
{
    TestAufgabe::CPgmAverager pgmAverager;
    try {
        pgmAverager.addSource(std::string{"./data/a.pgm"});
        pgmAverager.addSource(std::string{"./data/b.pgm"});
        FAIL() << "Expected std::runtime_error";
    } catch(std::runtime_error const &ex) {
        ASSERT_EQ(ex.what(), std::string("Parse Pgm failed. Size is different in the first source. ./data/b.pgm"));
    }
}


// negative test for catching exeception
TEST(UT_PgmAverager, addTwoPgmSourceButDifferentMaxGrayValue) 
{
    TestAufgabe::CPgmAverager pgmAverager;
    try {
        pgmAverager.addSource(std::string{"./data/a.pgm"});
        pgmAverager.addSource(std::string{"./data/a2.pgm"});
        FAIL() << "Expected std::runtime_error";
    } catch(std::runtime_error const &ex) {
        ASSERT_EQ(ex.what(), std::string("Parse Pgm failed. Max grayvalue is different in the first source. ./data/a2.pgm"));
    }
}


// negative test for catching exception
TEST(UT_PgmAverager, produceWithZeroPgmSource) 
{
    TestAufgabe::CPgmAverager pgmAverager;
    try {
        pgmAverager.produce(std::string{"./data/average.pgm"});
        FAIL() << "Expected std::logic_error";
    } catch(std::logic_error const &ex) {
        ASSERT_EQ(ex.what(), std::string("Not initialized"));
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
