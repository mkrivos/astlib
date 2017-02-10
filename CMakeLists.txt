project (astlib)
cmake_minimum_required(VERSION 3.3)

include_directories(.)

set(CMAKE_CXX_STANDARD 11) 

if (MSVC)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -march=native -Wall -O0")
endif()

find_package(Poco 1.7.0 REQUIRED COMPONENTS Net Util XML JSON Foundation CONFIG PATHS "/opt/rsys/platform" "d:/opt/rsys/platform")

if ( NOT Poco_FOUND)
  message(FATAL_ERROR "Package Poco and it's components required, but not found!")
endif()

add_subdirectory(astlib obj/astlib)

set(LIBS astlib ${Poco_LIBRARIES} ${SYSTEM_LIBS})
include_directories(${Poco_INCLUDE_DIRECTORIES})

add_executable(loader src/loader.cpp)
target_link_libraries(loader ${LIBS})

add_executable(ast2json src/ast2json.cpp)
target_link_libraries(ast2json ${LIBS})

# Setup GTEST testing
find_package(GTest)
if (GTEST_FOUND)
    enable_testing()
    include_directories(${GTEST_INCLUDE_DIR})
    message(STATUS "Found GTest: ${GTEST_LIBRARY}")
endif()

# Test units
if (GTEST_FOUND)
aux_source_directory ( tests/unit tu_srcs2)
add_executable       ( testunit ${tu_srcs2} )
IF (RELEASE)
    target_link_libraries( testunit ${RUNTIME} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})
else()
    IF ( CMAKE_SYSTEM MATCHES "Windows")
        target_link_libraries( testunit ${LIBS} ${GTEST_LIBRARY_DEBUG} ${GTEST_MAIN_LIBRARY_DEBUG})
    else()
        target_link_libraries( testunit ${LIBS} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})
    endif()
endif()
#set_target_properties( testunit PROPERTIES COMPILE_FLAGS "${CFLAGS}" )
endif()