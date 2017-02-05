project (astlib)
cmake_minimum_required(VERSION 3.3)

include_directories(.)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

#set(CMAKE_PREFIX_PATH "/opt/rsys/platform")
find_package(Poco 1.7.0 REQUIRED COMPONENTS Foundation CONFIG PATHS "/opt/rsys/platform")

if ( NOT Poco_FOUND)
  message(FATAL_ERROR "Package Poco and it's components required, but not found!")
endif()

set(LIBS astlib ${Poco_LIBRARIES} ${SYSTEM_LIBS})
include_directories(${Poco_INCLUDE_DIRECTORIES})

add_subdirectory(astlib obj/astlib)

add_executable(loader src/loader.cpp)
target_link_libraries(loader ${LIBS})

