cmake_minimum_required(VERSION 3.31)
project(search_engine VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include)
# Add source files
add_executable(search_engine
    main.cpp
    cpp/indexer.cpp
    cpp/id_generator.cpp
)


