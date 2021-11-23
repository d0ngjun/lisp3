cmake_minimum_required(VERSION 3.0.0)
project(lisp3 VERSION 0.1.0)

#include(CTest)
#enable_testing()

#include_directories(source)
file(GLOB_RECURSE SOURCE source/*.cc)
add_executable(lisp3 ${SOURCE})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#add_compile_options(-Wall -Wextra -pedantic -Werror)
add_compile_options(-Wall -Werror)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

