cmake_minimum_required(VERSION 3.11)

# Project name and version
project(CppTestAufgabe VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_BUILD_TYPE Debug)

# setup code format tool
find_program(FORMAT_PROGRAM NAMES clang-format clang-format-8 clang-format-7 clang-format-6)

if(FORMAT_PROGRAM)
    set(FIND_COMMAND "find \
        ${PROJECT_SOURCE_DIR}/src \
        ${PROJECT_SOURCE_DIR}/test \
        -regex '.*\\.\\(c\\|cc\\|cpp\\|cxx\\|h\\|hh\\|hpp\\|hxx\\)$'")

add_custom_target(codeformat
    VERBATIM
    COMMAND bash -c "${FIND_COMMAND} | xargs -n 1 ${FORMAT_PROGRAM} -i"
)
endif()


# setup Googletest
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

# main source
add_subdirectory(src) 

 # unit testing
add_subdirectory(test)
