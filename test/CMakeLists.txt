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

add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:${TARGET}>/data
)