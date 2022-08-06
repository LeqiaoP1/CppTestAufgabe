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

To run
```
cd build/test
./UT_PgmAverager
```
The "case1_average.pgm" and "case2_average.pgm" will be generated for manually checking

### Evaluation with real .pmg data

from the "/workspace/build",
```
make install
```

The binary executable is then installed as "/workspace/build/bin/testCli"


The .pgm files from real world are located in "/workspace/data". 

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



