# unit testing
set(TARGET UT_PgmAverager)

set(SRC
        UT_CPgmAveragerTest.cpp
    )

add_executable(${TARGET} ${SRC})


target_link_libraries(${TARGET} PRIVATE
        GTest::gtest_main
        libtestaufgabe
)
