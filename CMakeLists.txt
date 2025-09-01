cmake_minimum_required(VERSION 3.28)

project(crapper)

add_executable(${CMAKE_PROJECT_NAME} source/main.c)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
#target_link_libraries(${CMAKE_PROJECT_NAME} curl)
