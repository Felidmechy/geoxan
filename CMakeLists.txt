cmake_minimum_required(VERSION 3.5)

project(geoxan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/SFML-2.5.1)

add_executable(geoxan ${CMAKE_SOURCE_DIR}/src/main.cpp)

target_include_directories(geoxan PRIVATE ${CMAKE_SOURCE_DIR}/inc)

target_link_libraries(geoxan sfml-system)
target_link_libraries(geoxan sfml-window)
target_link_libraries(geoxan sfml-graphics)

set_target_properties(geoxan PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/game
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/game
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/game
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/game
  LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/game
  LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/game
)

add_custom_command(TARGET geoxan POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/lib/SFML-2.5.1 ${CMAKE_SOURCE_DIR}/game)



install(TARGETS geoxan
        DESTINATION ${CMAKE_SOURCE_DIR}/game)
