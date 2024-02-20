cmake_minimum_required(VERSION 3.25)
project(wet1_winter2024)

set(CMAKE_CXX_STANDARD 17)

add_executable(wet1_winter2024 Olympicsa1.cpp wet1util.h Node.h AVL_tree.h Country.cpp Country.h Team.cpp Team.h Contestant.cpp Contestant.h ContestantID.cpp ContestantID.h ContestantStr.cpp ContestantStr.h StrCond.h StrCond.cpp
        maina1.cpp
        rankTreeTester.cpp)
