cmake_minimum_required(VERSION 3.17)
project(Poker)

set(CMAKE_CXX_STANDARD 14)

add_executable(Poker Play_Game.cpp Cards.h Cards.cpp Player.h Player.cpp Poker_Game.cpp Poker_Game.h)