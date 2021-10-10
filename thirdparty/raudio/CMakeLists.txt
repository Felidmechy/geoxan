cmake_minimum_required(VERSION 3.5)

project(raudio LANGUAGES C)

add_library(raudio STATIC ${CMAKE_CURRENT_LIST_DIR}/src/raudio.c)

find_package(Threads REQUIRED)
target_link_libraries(raudio Threads::Threads)
target_link_libraries(raudio ${CMAKE_DL_LIBS})

add_compile_definitions(RAUDIO_STANDALONE)

add_compile_definitions(SUPPORT_FILEFORMAT_WAV)
add_compile_definitions(SUPPORT_FILEFORMAT_OGG)
add_compile_definitions(SUPPORT_FILEFORMAT_FLAC)
add_compile_definitions(SUPPORT_FILEFORMAT_MP3)