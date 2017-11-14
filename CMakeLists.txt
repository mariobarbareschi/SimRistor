cmake_minimum_required(VERSION 3.3)
project("SimRistor" VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DENABLE_DEBUG_MACRO")
set(CMAKE_BUILD_TYPE debug)


# Add sources subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

# Target: clang-chimera
add_executable(simristor src/main.cpp)
# Includes
target_include_directories(simristor
                           PRIVATE ${CMAKE_SOURCE_DIR}/inc
                           )
target_link_libraries(simristor PRIVATE memristor xbar fblccontroller fblcrun)
