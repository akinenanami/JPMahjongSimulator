CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(JPMahjongSimulator)

SET(CMAKE_CXX_STANDARD 17)

ADD_EXECUTABLE(JPMahjongSimulator main.cpp CommonHeaders.h PlayerResources.h PlayResources.cpp Round.h Round.cpp)
