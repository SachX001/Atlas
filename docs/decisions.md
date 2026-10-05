# Atlas Architecture Decisions

This document records decisions that shape the project. It should be updated when a decision changes or a new long-term constraint is introduced.

## ADR-001: Build the MVP on a Single Machine

**Status:** Accepted

Atlas will first implement the complete crawl-to-search pipeline in one process or on one machine.

**Reason:**

The project is intended to develop understanding of the complete system before introducing distributed coordination, queues, replication, and failure recovery.

**Consequence:**

Distributed workers, Redis, container orchestration, and sharded indexes are deferred.

## ADR-002: Use C++ for the Core System

**Status:** Accepted

C++20 is the primary language for crawler, indexing, ranking, and performance-sensitive components.

**Reason:**

The project specifically targets practical experience with networking, memory management, data structures, concurrency, and performance.

**Consequence:**

The implementation must maintain clear ownership, error, and concurrency boundaries. Python may be introduced later for API and development tooling.

## ADR-003: Use CMake for Builds

**Status:** Accepted

CMake is the build-system entry point and the project targets C++20.

**Reason:**

CMake provides a portable build description and integrates with the selected test and dependency workflows.

**Consequence:**

Build instructions should work from a clean checkout and should not depend on IDE-specific project files.

## ADR-004: Use Small Initial Dependencies

**Status:** Accepted

The project uses Boost.URL for URL parsing and GoogleTest for testing. HTML parsing and persistence dependencies will be added when those components are implemented.

**Reason:**

The project focuses on crawler and search architecture rather than reimplementing standards-compliant URL or HTML parsing.

**Consequence:**

Dependencies should be added deliberately and documented when introduced.

## ADR-005: Use Structured Results for Expected Failures

**Status:** Accepted

Expected input and operational failures should be returned as structured results or empty/optional values. Exceptions are reserved for unexpected programming failures and broken invariants.

**Reason:**

Invalid CLI input, network failures, duplicate URLs, and malformed documents are normal operating conditions for a crawler.

**Consequence:**

Component boundaries must make failure information available to callers without requiring exception-driven control flow.

## ADR-006: Keep the Initial CLI Small

**Status:** Accepted

The initial crawler CLI supports repeated seed URLs, page limits, request timeout, crawl delay, and help:

```text
--seed <URL>
--max-pages <N>
--timeout <seconds>
--delay-ms <milliseconds>
--help
```

**Reason:**

The foundation should establish a stable interface without predicting options that belong to later crawler features.

**Consequence:**

Options such as maximum depth, output paths, concurrency, recrawling, and robots.txt controls will be introduced when their implementations are ready.

