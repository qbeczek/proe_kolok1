cmake_minimum_required(VERSION 3.11)

# nazwa projektu
project(wyk8)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# dodanie plikow wykonywalnych
add_executable(wyk8 candidate.cpp politycal_party.cpp constituency.cpp main.cpp electoral_system.cpp electoral_system_builder.cpp dHondt_method.cpp)

# specyfikacja standardu jezyka C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

