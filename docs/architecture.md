# Atlas Architecture

## Purpose

Atlas is an educational web crawler and search engine. Its architecture is intentionally introduced in stages so that each component can be implemented, tested, measured, and understood before the system becomes more complex.

The first target is a single-machine search pipeline. Distributed crawling, sharded indexes, and service infrastructure are deliberately deferred.

## Target Data Flow

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
HTML Parser ------> Discovered URLs
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

## Components

### URL Frontier

The frontier will manage URLs waiting to be crawled. It will eventually own normalization, duplicate detection, crawl state, depth limits, page limits, and scheduling.

### Crawler

The crawler will download pages over HTTP/HTTPS. It will handle timeouts, redirects, status codes, content types, retries, rate limits, and robots.txt as the implementation matures.

### Parser

The parser will convert downloaded HTML into useful document data: title, text, metadata, and links. A parsing library will be used instead of implementing the HTML standard from scratch.

### Document Store

The document store will persist crawled document metadata and extracted content. SQLite is the planned initial persistence technology.

### Indexer

The indexer will tokenize documents and build an inverted index. The initial index will support term lookup and basic relevance scoring.

### Query and Ranking

The query layer will normalize user queries, retrieve candidate documents, score them, and produce titles, URLs, and snippets. TF-IDF is the initial ranking target; BM25 and link-based ranking are later milestones.

## Phase 1 Foundation

The current foundation provides:

- C++20 and CMake project setup
- Shared URL, document, crawl-state, and configuration models
- Initial crawler CLI contract
- Basic logging
- URL parsing through Boost.URL
- GoogleTest-based foundation tests

HTTP crawling, HTML parsing, persistence, indexing, and search are not yet implemented.

## Design Boundaries

- `common/` contains shared models and small cross-cutting utilities.
- `apps/` contains executable entry points.
- Component-specific behavior belongs in its corresponding component directory.
- The crawler will begin as a single worker.
- New infrastructure should be introduced only when a current requirement justifies it.

