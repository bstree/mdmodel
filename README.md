# mdmodel

A small Markdown model parser library that builds a node tree from CommonMark syntax.

## Build

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

If CMake is not installed, install it first for your system.

## Run tests

```bash
cd build
ctest -V
```

or run the test executable directly:

```bash
./mdmodel_test
```

## Disable tests

```bash
mkdir -p build
cd build
cmake -DBUILD_TESTS=OFF ..
cmake --build .
```
