cmake_minimum_required(VERSION 3.24)
project(notMario)
include_directories(${SFML_INCLUDE_DIR})

set(SFML_DIR "D:/program/notMario/SFML/lib/cmake/SFML")

include_directories("D:/program/notMario/SFML/include/")

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.6 REQUIRED COMPONENTS graphics audio window system)

add_executable(notMario main.cpp)
target_link_libraries(notMario sfml-graphics sfml-audio sfml-window sfml-system)


