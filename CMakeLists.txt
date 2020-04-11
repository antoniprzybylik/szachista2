cmake_minimum_required(VERSION 3.10)

# nazwa projektu
project(szachista VERSION 2.0)

# standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# plik konfiguracyjny
configure_file(szachistaConfig.h.in szachistaConfig.h)

# plik wykonywalny
add_executable(szachista szachista.cpp)

target_include_directories( szachista PUBLIC "${PROJECT_BINARY_DIR}" )
