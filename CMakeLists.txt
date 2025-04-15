cmake_minimum_required(VERSION 3.30)
project(lists)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lists
    circular.h
    double.h
    forward.h
    list.h
    main.cpp
    tester.h)
