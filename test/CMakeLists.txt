cmake_minimum_required(VERSION 3.12)
project(testVm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-psabi -pthread -Wall -g")

get_filename_component(BASE_APP_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../ REALPATH)

add_definitions(
    -DLOGURU_WITH_STREAMS=1
)

add_executable(
    testVm
        testVm.cpp
        ${BASE_APP_PATH}/external/loguru/loguru.cpp
        ${BASE_APP_PATH}/src/vm.cpp
)

include_directories(
    testVm
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${BASE_APP_PATH}/include
        ${BASE_APP_PATH}/external/loguru
)

target_link_libraries(
    testVm 
        gtest 
        gtest_main 
        ${CMAKE_DL_LIBS}
)