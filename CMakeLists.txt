cmake_minimum_required(VERSION 3.18)

set(PROJECT_NAME "stuff")
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)

add_executable(lsmsg src/lsmsg.cpp)

add_executable(minefield src/minefield.cpp)

add_executable(ceasar_cipher src/ceasar_cipher.cpp)

add_executable(linked_list src/linked_list.cpp)

add_executable(t src/t.cpp)

add_executable(dijkstra src/dijkstra.cpp)

add_executable(a_stern src/a_stern.cpp)

add_executable(perlin_noise src/perlin_noise.cpp)
target_include_directories(perlin_noise PUBLIC include)

add_executable(rng src/rng_test.cpp)
target_include_directories(rng PUBLIC include)

add_executable(po_tests src/po_tests.cpp)
target_link_libraries(po_tests boost_program_options)

add_executable(ascii src/ascii.cpp)

add_executable(fib src/fibonacci.cpp)

add_executable(dct src/dct.cpp)

add_executable(lzw src/lzw.cpp)
target_include_directories(lzw PUBLIC include)

add_executable(sync_with_stdio src/sync_with_stdio.cpp)
target_include_directories(sync_with_stdio PUBLIC include)