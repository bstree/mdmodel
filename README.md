# mdmodel

mdmodel is a small C++ Markdown parser library that builds a node tree
from CommonMark input. It's header-only-compatible for simple projects and
provides a CMake target for linking into larger applications.

**Quick Start**

Prerequisites: CMake (>= 3.10), a C++ compiler (GCC/Clang/MSVC).

Build (default: builds library and tests):

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

Run tests:

```bash
cd build
ctest -V
# or run the test binary directly
./mdmodel_test
```

Disable building tests:

```bash
mkdir -p build
cd build
cmake -DBUILD_TESTS=OFF ..
cmake --build .
```

Usage notes
- The public headers are in the `include/` directory. Link against the
	`mdmodel` target from your CMake project: `target_link_libraries(myapp PRIVATE mdmodel)`.
- The test executable is `mdmodel_test` (built when `BUILD_TESTS=ON`).

Contributing
- Bug reports and PRs are welcome. Please follow the existing code style and
	add tests for new features when possible.

License
- This project is available under the terms in the `LICENSE` file.

Contact
- Open an issue for questions or feature requests.
