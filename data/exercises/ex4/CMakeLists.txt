cmake_minimum_required(VERSION 2.8.1)

project(Math)

include_directories(
./src/add
./src/mul
)

link_directories(
)

file(GLOB sources src/*/*.cpp)

add_executable(ex2test1 ./src/ex2test1.cpp ${sources})
add_executable(ex2test2 ./src/ex2test2.cpp ${sources})

target_link_libraries(ex2test1 stdc++ mpi metis)
target_link_libraries(ex2test2 stdc++ mpi metis)

install(TARGETS ex2test1 ex2test2 RUNTIME DESTINATION /home/s.engkadac/cmakecourse/ex2/bin)
