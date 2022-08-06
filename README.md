# CppTestAufgabe

### Dependencies

| Dependency         | Functionality delivered               |
|--------------------|---------------------------------------|
| CMake (ver3.11+)   | Building tool                         |
| ClangFormat        | Code formatter                        |
| git                | Download googletest                   |
| build-essential    | g++ compiler with c++17 support       |

### Building enviroment in Docker container (based on "ubuntu:20.04")
To build image (target image as "testaufgabe")
```
docker build -t testaufgabe .
```

To enter the container interactive for the following steps.
```
docker run -it --mount src="$(pwd)",target=/workspace,type=bind testaufgabe
```

### Compile ("out-of-source")

Assume that inside the container, for source compiliation:
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

