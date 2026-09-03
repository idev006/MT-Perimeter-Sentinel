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

add_executable(mps_sim simulator/main.cpp)
target_link_libraries(mps_sim PRIVATE mps)

enable_testing()
function(add_mps_test target source)
  add_executable(${target} ${source})
  target_link_libraries(${target} PRIVATE mps)
  add_test(NAME ${target} COMMAND ${target})
endfunction()

add_mps_test(mps_tests tests/test_main.cpp)
add_mps_test(mps_test_delivery tests/test_delivery.cpp)
add_mps_test(mps_test_security tests/test_security.cpp)
add_mps_test(mps_test_lifecycle tests/test_lifecycle.cpp)

set(MPS_TARGETS mps mps_sim mps_tests mps_test_delivery mps_test_security mps_test_lifecycle)
foreach(target ${MPS_TARGETS})
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    if(MPS_ENABLE_SANITIZERS)
      target_compile_options(${target} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
      target_link_options(${target} PRIVATE -fsanitize=address,undefined)
    endif()
  endif()
endforeach()
