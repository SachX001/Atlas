# Atlas Development Guide

## Prerequisites

Install:

- CMake 3.20 or newer
- A C++20-compatible compiler
- Git
- Ninja or another supported CMake generator

The first CMake configure step downloads GoogleTest and Boost.URL through `FetchContent`, so network access may be required.

## Configure and Build

From the repository root:

```bash
cmake -S . -B build
cmake --build build
```

The main targets are:

```text
atlas-crawler
atlas-indexer
atlas-search
atlas-tests
```

## Run Tests

```bash
ctest --test-dir build --output-on-failure
```

Run the test executable directly when focused debugging is needed:

```bash
build/atlas-tests
```

On Windows, use the generated executable path, for example:

```powershell
.\build\atlas-tests.exe
```

## CLI Development Contract

The initial crawler CLI is intentionally small:

```text
--seed <URL>               Seed URL; repeatable
--max-pages <N>            Maximum number of pages
--timeout <seconds>        Request timeout
--delay-ms <milliseconds>  Delay between requests
--help                     Show help
```

The CLI currently validates configuration and starts the crawler application shell. Network crawling will be added in the next implementation phase.

## Change Workflow

1. Create a focused feature branch.
2. Keep changes within the relevant component boundary.
3. Add or update tests with behavior changes.
4. Build the project and run the test suite.
5. Update documentation when interfaces or decisions change.
6. Commit with a clear, specific message.

## Code Guidelines

- Use C++20 consistently.
- Prefer clear data types and small functions.
- Use structured results for expected failures.
- Reserve exceptions for unexpected failures and broken invariants.
- Keep comments focused on decisions or non-obvious behavior.
- Avoid adding infrastructure before the current architecture needs it.

## Current Development Sequence

The planned order is:

```text
Foundation
    -> URL frontier
    -> HTTP crawler
    -> HTML parser
    -> document storage
    -> inverted index
    -> query and ranking
    -> search API
```

