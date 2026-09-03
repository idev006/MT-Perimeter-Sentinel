cmake_minimum_required(VERSION 3.20)
project(MTPerimeterSentinel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MPS_ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

find_package(OpenSSL REQUIRED)

add_library(mps firmware/src/mps.cpp firmware/src/host_auth.cpp)
target_include_directories(mps PUBLIC firmware/include)
target_link_libraries(mps PUBLIC OpenSSL::Crypto)

add_executable(mps_tests tests/test_main.cpp)
target_link_libraries(mps_tests PRIVATE mps)

add_executable(mps_sim simulator/main.cpp)
target_link_libraries(mps_sim PRIVATE mps)

foreach(target mps mps_tests mps_sim)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    if(MPS_ENABLE_SANITIZERS)
      target_compile_options(${target} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
      target_link_options(${target} PRIVATE -fsanitize=address,undefined)
    endif()
  endif()
endforeach()

enable_testing()
add_test(NAME mps_tests COMMAND mps_tests)
