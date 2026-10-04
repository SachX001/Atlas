cmake_minimum_required(VERSION 3.20)

project(Atlas VERSION 0.1.0 LANGUAGES CXX)

enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

set(BOOST_INCLUDE_LIBRARIES url)

FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.89.0/boost-1.89.0-cmake.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(Boost)
    

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

add_executable(atlas-tests
    	tests/smoke_test.cpp
	common/url.cpp
)

target_link_libraries(atlas-tests
       PRIVATE
       GTest::gtest_main
       Boost::url
)

include(GoogleTest)

gtest_discover_tests(atlas-tests)

	

