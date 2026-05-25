# mdmodel

`mdmodel` is a lightweight C++ semantic Markdown modeling library built on top of CommonMark (`cmark`).

Instead of treating Markdown as a rendering format only, `mdmodel` exposes Markdown documents as a semantic hierarchical node tree that can be used for:

- Configuration systems
- UI DSLs
- Structured human-readable data
- Semantic parsing
- Tree-based application models

The library acts as an adapter layer over `cmark`, providing a clean C++ API for traversing and interpreting Markdown documents.

## Design Goals

- Lightweight
- Minimal allocations
- Semantic tree abstraction
- Human-readable configuration
- No rendering logic
- No application-specific behavior
- Separation between parsing and semantic interpretation

## Non-Goals

`mdmodel` is **not**:

- A Markdown renderer
- A UI framework
- A replacement for CommonMark
- A schema system

The library focuses only on exposing a semantic tree structure over Markdown documents.

---

## Example

Markdown input:

```markdown
# Window
  - width: 240
  - height: 64

# Layout
  - StatusBar
    - BatteryIndicator
    - BluetoothIndicator
```

Semantic tree:

Window
 ├── width
 │    └── 240
 └── height
      └── 64

Layout
 └── StatusBar
      ├── BatteryIndicator
      └── BluetoothIndicator



## Architecture

        Markdown Text
             ↓
           cmark
             ↓
      mdmodel AST Adapter
             ↓
Application-specific semantic parsers



The library intentionally keeps semantic interpretation outside the core model layer.

For example:

auto width = node.IntValue();
auto enabled = node.BoolValue();

Typed accessors are interpreted lazily while the underlying model remains text-based.



## Building

Requirements:

CMake >= 3.10
C++17 compiler
libcmark

Build:

mkdir -p build
cd build
cmake ..
make

Run tests:

ctest

Install system-wide:

sudo cmake --install .
sudo ldconfig




## Using mdmodel

After installation:

find_library(MDMODEL_LIB mdmodel REQUIRED)

target_link_libraries(myapp PRIVATE ${MDMODEL_LIB})

Example include:
``` c++
#include <mdmodel/Document.hpp>
```



## Intended Usage

mdmodel was originally created as part of a Markdown-driven UI system experiment, where Markdown documents describe UI layouts, widgets, and bindings using hierarchical semantic structures.

The library is intentionally generic enough to support other structured Markdown applications.



## Future Direction

###Potential future additions:

Typed value helpers
Tree traversal iterators
Semantic query helpers
Config-oriented parsing utilities
Optional schema validation layers


##License

See LICENSE.


## Contributing

Issues, ideas, and pull requests are welcome.


