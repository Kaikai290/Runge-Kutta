cmake_minimum_required(VERSION 3.10.2)

project(Runge-Kutta)

add_executable(${PROJECT_NAME} WIN32 main.cpp) 

target_link_libraries(${PROJECT_NAME} Winmm.lib)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
