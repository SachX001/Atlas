# Atlas Testing Strategy

## Testing Goals

Testing is part of the implementation process. Each component should have a small, deterministic test surface before it is connected to the rest of the system.

## Running Tests

Configure and build the project:

```bash
cmake -S . -B build
cmake --build build
```

Run all registered tests:

```bash
ctest --test-dir build --output-on-failure
```

## Current Foundation Tests

The current test suite covers:

- Basic URL parsing
- Document data storage
- Crawl-state values
- Configuration values
- Valid CLI arguments
- Missing and invalid CLI arguments
- Unknown CLI options
- Logging calls

The tests are currently grouped in `tests/smoke_test.cpp`. They may be split into component-specific files as the project grows.

## Planned Test Layers

### Unit Tests

Unit tests should cover:

- URL normalization
- URL deduplication
- Configuration validation
- Tokenization
- Index operations
- Query parsing
- Ranking calculations

### Parser Tests

Parser tests should use local HTML fixtures to verify:

- Title extraction
- Text extraction
- Link extraction
- Metadata handling
- Malformed HTML behavior

### Integration Tests

The crawler pipeline should be tested as:

```text
Crawler -> Parser -> Document Store
```

The search pipeline should be tested as:

```text
Indexer -> Search -> Ranking
```

### Failure Tests

Expected failures should be tested explicitly, including:

- Invalid URLs
- Missing CLI values
- Network timeouts
- HTTP 4xx and 5xx responses
- Unsupported content types
- Malformed HTML
- Duplicate URLs
- Storage failures

### Performance Tests

Once crawling and indexing exist, record:

- Pages crawled per second
- Average request latency
- Number of unique and duplicate URLs
- Indexing time
- Search latency
- Memory usage

Performance changes should be supported by measurements rather than assumptions.

## Test Quality Rules

- Tests should be deterministic and repeatable.
- Network-dependent tests should use a local test server or controlled fixtures.
- Tests should verify behavior, not implementation details.
- Every expected failure should have a clear assertion.
- A single failing page should not make the complete crawler test fail unexpectedly.

