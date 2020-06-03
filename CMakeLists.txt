cmake_minimum_required(VERSION 3.12)
project(vm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-psabi -pthread -Wall -g")

add_definitions(
    -DLOGURU_WITH_STREAMS=1
)

add_subdirectory(test)