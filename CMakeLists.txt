cmake_minimum_required(VERSION 3.9)
project(Calculator)

set(CMAKE_CXX_STANDARD 11)

add_executable(Calculator main.cpp Token.cpp Token.h shuntingyard.cpp shuntingyard.h calculator.cpp calculator.h CalculatorTests.cpp CalculatorTests.h)