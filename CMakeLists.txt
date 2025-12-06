cmake_minimum_required(VERSION 3.26)
project(HW1_2526A)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HW1_2526A
    BlockChain.h
    Transaction.cpp
    Transaction.h
    Utilities.cpp
    Utilities.h)
