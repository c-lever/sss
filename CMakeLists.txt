cmake_minimum_required(VERSION 3.5)

project(01.guess_the_number_game)

add_executable(guess_the_number_game
    main.cpp
    table.cpp
    table.h
)

set_target_properties(guess_the_number_game PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
