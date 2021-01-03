cmake_minimum_required(VERSION 3.15)
project(code)

set(CMAKE_CXX_STANDARD 14)

add_executable(code Basic/Basic.cpp
        Basic/evalstate.cpp Basic/evalstate.h
        Basic/exp.cpp Basic/exp.h
        Basic/parser.cpp Basic/parser.h
        Basic/program.cpp Basic/program.h
        Basic/statement.cpp Basic/statement.h
        StanfordCPPLib/error.cpp StanfordCPPLib/error.h
        StanfordCPPLib/tokenscanner.cpp StanfordCPPLib/tokenscanner.h
        StanfordCPPLib/simpio.cpp StanfordCPPLib/simpio.h
        StanfordCPPLib/strlib.cpp StanfordCPPLib/strlib.h)
