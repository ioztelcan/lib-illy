cmake_minimum_required(VERSION 3.24)

project(utillyty VERSION 2.0.0 LANGUAGES CXX)

# Add the library target
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set C++ standard to 17
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

# Add compile options
target_compile_options(${PROJECT_NAME} INTERFACE
        -Wall
        -Werror
        -fsanitize=address
        )

# Add link options
target_link_options(${PROJECT_NAME} INTERFACE
        -fsanitize=address
        )

#if(ENABLE_TESTING)
  add_subdirectory(gtest)
#endif()

