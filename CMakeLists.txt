cmake_minimum_required(VERSION 3.28.1)
project(FlappyBird)

include(cmake/FetchEngine.cmake)
include(cmake/FetchKiosk.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g -gdwarf-2 -Wall -Wextra -Wpedantic -fsanitize=address,undefined -fno-omit-frame-pointer")

set(LATEBIT_VERSION "v0.9.0")

file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
  fetch_latebit(${LATEBIT_VERSION} "wasm")
  file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
  
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/public)
  fetch_latebit_kiosk("v0.0.4" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

  add_executable(index main.cpp ${SRC_FILES})
  set_target_properties(index PROPERTIES LINK_FLAGS "-sUSE_SDL=2 -sUSE_LIBPNG=1 -sSTACK_SIZE=1MB -sEXPORTED_RUNTIME_METHODS=['callMain'] --preload-file assets")
  target_include_directories(index PRIVATE ${CMAKE_SOURCE_DIR}/src)
  target_link_libraries(index PRIVATE latebit)
else()
  fetch_latebit(${LATEBIT_VERSION} ${CMAKE_SYSTEM_NAME})

  add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})
  target_link_libraries(${PROJECT_NAME} PRIVATE latebit)
  target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
endif()