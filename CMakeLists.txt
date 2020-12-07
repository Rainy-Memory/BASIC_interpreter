cmake_minimum_required(VERSION 3.17)
project(BASIC_interpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(BASIC_interpreter Basic/Basic.cpp
        Basic/evalstate.cpp Basic/evalstate.h
        Basic/exp.cpp Basic/exp.h
        Basic/parser.cpp Basic/parser.h
        Basic/program.cpp Basic/program.h
        Basic/statement.cpp Basic/statement.h
        StanfordCPPLib/error.cpp StanfordCPPLib/error.h
        StanfordCPPLib/tokenscanner.cpp StanfordCPPLib/tokenscanner.h
        StanfordCPPLib/simpio.cpp StanfordCPPLib/simpio.h
        StanfordCPPLib/strlib.cpp StanfordCPPLib/strlib.h
        )