 cmake_minimum_required(VERSION 2.8.12)
 project(DCDB)

 add_definitions("-std=c++11")

 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup()

 include_directories(src)
 file(GLOB_RECURSE PROJECT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

 set(PROJECT_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
 list(REMOVE_ITEM PROJECT_SOURCE ${PROJECT_MAIN})

 include_directories(${CONAN_INCLUDE_DIRS})
 add_library(dcdblib STATIC ${PROJECT_SOURCE})

 add_executable(dcdb src/main.cpp)
 target_link_libraries(dcdb dcdblib ${CONAN_LIBS})