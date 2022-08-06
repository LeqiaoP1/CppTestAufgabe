# CppTestAufgabe

### Dependencies

| Dependency         | Functionality delivered               |
|--------------------|---------------------------------------|
| CMake (ver3.11+)   | Building tool                         |
| ClangFormat        | Code formatter                        |
| git                | Download googletest                   |
| build-essential    | g++ compiler with c++17 support       |


### Compile ("out-of-source")

To compile:
```
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### Unit tests

Unit tests got compiled by default.

Some very simple .pgm fiels in "test/data" for testing purpose

Tests binaries will be prefixed with `UT_`.

To run
```
cd build/test
./UT_PgmAverager
```
The "case1_average.pgm" and "case2_average.pgm" will be generated for manually checking

