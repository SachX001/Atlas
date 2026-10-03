cmake_minimum_required(VERSION 3.20)

project(Atlas VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSION OFF)

add_executable(atlas-crawler
    apps/crawler_main.cpp
)

add_executable(atlas-indexer
    apps/indexer_main.cpp
)

add_executable(atlas-search
    apps/search_main.cpp
)
