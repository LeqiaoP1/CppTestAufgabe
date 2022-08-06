# static lib project
set(TARGET libtestaufgabe)

set(SRC
    CPgmAverager.cpp
)

add_library(${TARGET} STATIC
    ${SRC}
)

target_include_directories(${TARGET}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
