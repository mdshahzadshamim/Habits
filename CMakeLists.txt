cmake_minimum_required(VERSION 3.28.3)
project(Habits VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_ITERATOR_DEBUG_LEVEL=0 /MD")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

# Set C++ standard to C++11 or later
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include libpqxx headers
include_directories("C:/Program Files/libpqxx/include" "C:/Program Files/PostgreSQL/16/lib")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")

add_executable(Habits Habits.cpp)

# Find and link against libpqxx
find_package(Libpqxx REQUIRED)
if(Libpqxx_FOUND)
    message(STATUS "Found libpqxx: ${Libpqxx_INCLUDE_DIR}")
    include_directories(${Libpqxx_INCLUDE_DIR})
    target_link_libraries(Habits PRIVATE ${Libpqxx_LIBRARY})
else()
    message(FATAL_ERROR "libpqxx not found")
endif()

# Link against libpq
target_link_libraries(Habits PRIVATE "C:/Program Files/PostgreSQL/16/lib/libpq.lib" "C:/Program Files/libpqxx/lib/pqxx.lib" )
target_link_libraries(Habits PRIVATE ws2_32.lib wsock32.lib)
target_link_libraries(Habits PRIVATE msvcrt )
target_link_libraries(Habits PRIVATE legacy_stdio_definitions )
# target_link_libraries(Habits PRIVATE stdc++fs)

# Set project name and version for CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set_property(TARGET Habits PROPERTY CXX STANDARD 20)
