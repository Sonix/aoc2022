cmake_minimum_required(VERSION 3.24)
project(aoc2022)

set(CMAKE_CXX_STANDARD 20)

add_executable(day1 day1.cpp)
add_executable(day2 day2.cpp)
add_executable(day3 day3.cpp)
add_executable(day4 day4.cpp)
add_executable(day5 day5.cpp)
add_executable(day6 day6.cpp)
add_executable(day7 day7.cpp)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    # a reasonably strict default set of warnings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
    # a really pedantic set of warnings (which still pays off...)
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -no-Wc++98-compat -Wno-c++98-c++11-compat")
endif()