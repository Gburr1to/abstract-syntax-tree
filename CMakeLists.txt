cmake_minimum_required(VERSION 4.0)
project(vaja10)

set(CMAKE_CXX_STANDARD 14)

add_executable(parser
        main.cpp
        Token.h
        Scanner.h
        Parser.h
        AST.h)
