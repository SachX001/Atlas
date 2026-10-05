# Atlas

Atlas is an educational web crawler and search engine built incrementally from first principles. The project explores networking, concurrent programming, data structures, information retrieval, persistence, and distributed systems.

The project follows one guiding principle:

> Build the simplest version that works, measure it, understand its limitations, and then improve it.

## Current Status

The repository currently contains the Phase 1 foundation. This phase establishes the shared models, build system, command-line contract, logging, and automated tests required for the crawler and search pipeline.

The actual HTTP crawler, HTML parser, document store, indexer, and search engine are planned for subsequent phases.

## Phase 1 Scope

Phase 1 provides:

- CMake-based C++20 project setup
- Separate application targets for the crawler, indexer, and search service
- Shared URL, document, crawl-state, and configuration models
- Initial crawler command-line interface
- Structured command-line validation errors
- Basic application logging
- GoogleTest-based foundation tests
- Boost.URL integration for URL parsing

Phase 1 deliberately does not include:

- HTTP requests
- URL queue or frontier processing
- HTML parsing
- Persistent storage
- Inverted indexing
- Search ranking
- Search API
- Concurrent or distributed workers

## Architecture Direction

Atlas is being developed as a series of small, testable components:

```text
Seed URLs
    |
    v
URL Frontier
    |
    v
Crawler
    |
    v
HTML Parser
    |
    +------> Discovered URLs
    |
    v
Document Store
    |
    v
Indexer
    |
    v
Search Index
    |
    v
Query and Ranking
```

The first working version will run on a single machine. Concurrency, persistent queues, and distributed services will be introduced only after the single-machine pipeline is reliable and measurable.

## Repository Layout

```text
Atlas/
├── apps/       Application entry points
├── common/     Shared models, CLI parsing, logging, and URL handling
├── crawler/    Future crawler implementation
├── parser/     Future HTML parsing implementation
├── storage/    Future document and crawl-state persistence
├── indexer/    Future inverted-index implementation
├── search/     Future query and ranking implementation
├── tests/      Automated tests
├── benchmarks/ Performance benchmarks
└── CMakeLists.txt
```

## Technology Stack

- C++20 for the core system
- CMake 3.20 or newer for builds
- Boost.URL for URL parsing
- GoogleTest for automated tests
- SQLite is planned for the initial persistence layer
- Python may be introduced later for the search API and development tooling

External dependencies are currently managed through CMake `FetchContent`. The first configure step may require network access to download GoogleTest and Boost.URL.

## Prerequisites

Install the following tools:

- CMake 3.20 or newer
- A C++20-compatible compiler
- Git
- Ninja or another supported CMake build system

On Windows, a MinGW, GCC, or Visual C++ toolchain may be used as long as it supports C++20 and is available to CMake.

## Build

From the repository root:

```bash
cmake -S . -B build
cmake --build build
```

The build produces these application targets:

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

The current foundation tests cover URL parsing, shared data models, configuration values, command-line validation, and logging calls.

## Crawler CLI Contract

The initial crawler interface is intentionally small:

```text
atlas-crawler [options]

--seed <URL>               Seed URL; repeatable
--max-pages <N>            Maximum number of pages to crawl
--timeout <seconds>        Per-request timeout
--delay-ms <milliseconds>  Minimum delay between requests
--help                     Show usage information
```

Example:

```bash
atlas-crawler \
  --seed https://example.com \
  --max-pages 100 \
  --timeout 10 \
  --delay-ms 250
```

Multiple seed URLs may be supplied by repeating `--seed`:

```bash
atlas-crawler \
  --seed https://example.com \
  --seed https://example.org \
  --max-pages 100
```

The following validation rules apply:

- At least one `--seed` is required.
- `--max-pages` is required and must be greater than zero.
- `--timeout` must be greater than zero.
- `--delay-ms` must not be negative.
- Unknown options and missing option values are rejected.

The crawler currently validates its configuration and starts the application shell. Network crawling will be added in the next phase.

## Error Handling

Atlas uses a simple component-level error policy:

```text
Expected input or operational failure
    -> return a structured result or empty/optional value

Unexpected programming failure or broken invariant
    -> throw an exception
```

Examples of expected failures include invalid CLI input, request timeouts, HTTP failures, duplicate URLs, and malformed documents. These should be handled by the owning component without terminating the complete process.

Unexpected exceptions are caught at the application boundary and reported through the logger.

The crawler uses these exit codes:

```text
0  Successful startup or --help
1  Unexpected application failure
2  Invalid command-line input
```

## Logging

The foundation provides three basic logging levels:

```text
[INFO]  Informational messages
[WARN]  Recoverable warnings
[ERROR] Error messages
```

The logger is intentionally small at this stage. Structured fields, timestamps, file output, and configurable log levels can be added when the crawler begins producing operational metrics.

## Development Workflow

Keep changes small and focused:

1. Create a feature branch.
2. Add or update tests with the implementation.
3. Build the project and run the test suite.
4. Update documentation when behavior or interfaces change.
5. Commit with a clear, specific message.

The foundation should remain independent of distributed infrastructure. New dependencies should be introduced only when they support an immediate project requirement.

## Next Phase

The next implementation phase is URL frontier and crawler reliability. It will add:

- URL normalization
- Duplicate detection
- Crawl depth and page limits
- URL state tracking
- HTTP/HTTPS requests
- Request timeouts and redirects
- Content-type validation
- Basic retry and failure handling
- Crawl progress logging

The first crawler milestone will be a command-line program that accepts seed URLs, downloads a controlled number of pages, extracts links, and avoids crawling the same normalized URL more than once.

## Project Principles

- Prefer simple, understandable components.
- Keep the single-machine system working before distributing it.
- Measure performance before optimizing.
- Treat testing and documentation as part of implementation.
- Introduce infrastructure only when the current requirements justify it.
