# CppTestAufgabe

### Dependencies

| Dependency         | Functionality delivered               |
|--------------------|---------------------------------------|
| CMake (ver.3.11+)  | Building tool                         |
| ClangFormat        | Code formatter                        |
| git                | Download googletest                   |
| build-essential    | c++ compiler with c++17 support       |
| docker             | Containerization                      |

### Building environment in Docker container (based on "ubuntu:20.04")
To build image (target image as "testaufgabe")
```
docker build -t testaufgabe .
```

To enter the container interactive for the following steps
```
docker run -it --mount src="$(pwd)",target=/workspace,type=bind testaufgabe
```
The host folder is mapped (mounted) into container's path "/workspace"


### Compile ("out-of-source")

Inside the container's directory "/workspace", for source compiliation:
```
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### Unit tests

Unit tests got compiled by default.

Some very simple .pgm files in "/workspace/test/data" for testing purpose

Tests binaries will be prefixed with `UT_`.

from the container's "/workspace/build"
```
cd test
./UT_PgmAverager
```

The "case1_average.pgm", "case2_average.pgm" and "case3_average.pgm" will be generated for manually checking

It may look like this.
```
root@d3362da700ec:/workspace/build/test# ./UT_PgmAverager 
Running main() from /workspace/build/_deps/googletest-src/googletest/src/gtest_main.cc
[==========] Running 9 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 9 tests from UT_PgmAverager
[ RUN      ] UT_PgmAverager.dummy
current path is: "/workspace/build/test"
[       OK ] UT_PgmAverager.dummy (0 ms)
[ RUN      ] UT_PgmAverager.addPgmSourceFormatUnsupported
Opps. PGM version is NOT P2
[       OK ] UT_PgmAverager.addPgmSourceFormatUnsupported (0 ms)
[ RUN      ] UT_PgmAverager.addTwoPgmSourceButDifferentSize
Opps. Input .pgm file has different size than the first .pgm.
[       OK ] UT_PgmAverager.addTwoPgmSourceButDifferentSize (0 ms)
[ RUN      ] UT_PgmAverager.addTwoPgmSourceButDifferentMaxGrayValue
Opps. Input .pgm file has different max grayvalue than the first .pgm.
[       OK ] UT_PgmAverager.addTwoPgmSourceButDifferentMaxGrayValue (0 ms)
[ RUN      ] UT_PgmAverager.produceWithoutPgmSource
[       OK ] UT_PgmAverager.produceWithoutPgmSource (0 ms)
[ RUN      ] UT_PgmAverager.produceWithOnePgmSource
./data/case1_average.pgm is generated. 
[       OK ] UT_PgmAverager.produceWithOnePgmSource (0 ms)
[ RUN      ] UT_PgmAverager.produceWithTwoPgmSource
./data/case2_average.pgm is generated. 
[       OK ] UT_PgmAverager.produceWithTwoPgmSource (0 ms)
[ RUN      ] UT_PgmAverager.produceAfterAddSourceException
Opps. Input .pgm file has different size than the first .pgm.
./data/case3_average.pgm is generated. 
[       OK ] UT_PgmAverager.produceAfterAddSourceException (0 ms)
[ RUN      ] UT_PgmAverager.produceAfterReset
[       OK ] UT_PgmAverager.produceAfterReset (0 ms)
[----------] 9 tests from UT_PgmAverager (0 ms total)

[----------] Global test environment tear-down
[==========] 9 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 9 tests.
```



### Evaluation with real .pmg data

from the container's "/workspace/build"
```
make install
cd bin
```

The binary executable is then installed as "/workspace/build/bin/testCli"


The .pgm files from real world are located in "/workspace/data". 

It may look like this.
```
root@c896d3e3bd27:/workspace/build/bin# ./testCli              
Usage: testCli -d <directory_path>
  where <directory_path>	in which input .pgm images and the output average.pgm are located
  example: testCli -d ./data
root@c896d3e3bd27:/workspace/build/bin# ./testCli -d ../../data
process "../../data/2020-08-11--00-01-10-310.pgm"
process "../../data/2020-08-11--00-01-09-490.pgm"
process "../../data/2020-08-11--00-01-09-252.pgm"
process "../../data/2020-08-11--00-01-09-553.pgm"
process "../../data/2020-08-11--00-01-09-073.pgm"
process "../../data/2020-08-11--00-01-08-913.pgm"
process "../../data/2020-08-11--00-01-09-916.pgm"
process "../../data/2020-08-11--00-01-08-805.pgm"
process "../../data/2020-08-11--00-01-10-119.pgm"
process "../../data/2020-08-11--00-01-09-732.pgm"
../../data/average.pgm is generated. 

```



