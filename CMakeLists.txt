project (astlib)
cmake_minimum_required(VERSION 3.3)

set (PROJECT_NAME "astlib")
set (PROJECT_LOG_MODULE_NAME "astlib")
set (PROJECT_CODENAME "${PROJECT_NAME}")
execute_process (
    COMMAND date "+%Y"
    OUTPUT_VARIABLE PROJECT_COPYRIGHT_YEARS
    OUTPUT_STRIP_TRAILING_WHITESPACE)
set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 9)
set (PROJECT_VERSION_PATCH 0)
set (PROJECT_VERSION_TYPE SNAPSHOT)
set (PROJECT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}-${PROJECT_VERSION_TYPE}")
set (PROJECT_VENDOR_ID "aero.rsys")
set (PROJECT_VENDOR_NAME "R-SYS s.r.o.")
set (PROJECT_VENDOR_URL "www.r-sys.sk")
set (PROJECT_ID "${PROJECT_VENDOR_ID}.${PROJECT_NAME}")

#
# Project Output Paths
#
set (MAINFOLDER ${PROJECT_SOURCE_DIR})
set (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
set (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

include_directories(.)
set(CMAKE_CXX_STANDARD 14) 
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
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

add_executable(binary2asterix examples/binary2asterix.cpp)
target_link_libraries(binary2asterix ${LIBS})

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