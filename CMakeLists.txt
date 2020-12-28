cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
project(libmahjonghttp)

set(BUILD_SHARED_LIBS TRUE)

find_package(RapidJSON REQUIRED)

add_subdirectory(${libmahjonghttp_SOURCE_DIR}/lib)

add_library(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "libmahjonghttp")

ProcessorCount(N)
if(NOT N EQUAL 0)
  set(CTEST_BUILD_FLAGS -j${N})
  set(ctest_test_args ${ctest_test_args} PARALLEL_LEVEL ${N})
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(libmahjong PRIVATE -pedantic -Wall -Wmost -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(libmahjong PRIVATE -pedantic -Wall -Wextra)
endif()

add_subdirectory(${libmahjonghttp_SOURCE_DIR}/src)

get_target_property(libmahjonghttp_sources libmahjonghttp SOURCES)

target_include_directories(${PROJECT_NAME} PUBLIC "${libmahjonghttp_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} libmahjong)
