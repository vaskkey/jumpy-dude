cmake_minimum_required(VERSION 3.16)
project(jumpydude LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB engine_SRC
     "Engine/**/*.hpp"
     "Engine/**/*.cpp"
     "Engine/Components/**/*.hpp"
     "Engine/Components/**/*.cpp"
     "Engine/AI/**/*.hpp"
     "Engine/AI/**/*.cpp"
     "Engine/Items/**/*.hpp"
     "Engine/Items/**/*.cpp"
)

add_executable(jumpydude main.cpp ${engine_SRC})
target_link_libraries(jumpydude PRIVATE sfml-graphics)
target_compile_features(jumpydude PRIVATE cxx_std_20)

install(TARGETS jumpydude)
