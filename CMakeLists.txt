cmake_minimum_required(VERSION 4.1.2)
project(usaco)

set(CMAKE_CXX_STANDARD 14)

add_executable(usaco
        past_contests/prob1_bronze_season26contest1/cpp/single_test_runner.cpp
        past_contests/prob1_bronze_season26contest1/cpp/solution.cpp
        past_contests/prob1_bronze_season26contest1/cpp/test_runner.cpp
        past_contests/prob2_silver_season26contest1/solution.cpp
        past_contests/prob2_silver_season26contest1/test.cpp
        past_contests/prob3_bronze_season26contest1/cpp/single_test_runner.cpp
        past_contests/prob3_bronze_season26contest1/cpp/solution.cpp
        past_contests/prob3_bronze_season26contest1/cpp/test_runner.cpp
        study_algo/algo.cpp
        usaco_guide/silver/prio_q/prio_q_demo.cpp
        usaco_guide/silver/prio_q/room_alloc.cpp
        usaco_guide/silver/flood_fill/counting_rooms.cpp
        usaco_guide/silver/tree/subordinates.cpp
        usaco_guide/silver/func_graph/coop_game.cpp
        usaco_guide/silver/func_graph/badge.cpp)
