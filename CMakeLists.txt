project (astlib)
cmake_minimum_required(VERSION 3.3)

include_directories(.)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# set the POCO paths and libs
set(POCO_PREFIX      "/opt/rsys/platform") 

# the directory containing "include" and "lib"
set(POCO_INCLUDE_DIR "${POCO_PREFIX}/include")
set(POCO_LIB_DIR     "${POCO_PREFIX}/lib")
set(POCO_LIBS        "${POCO_LIB_DIR}/libPocoUtild.so"
                     "${POCO_LIB_DIR}/libPocoJSONd.so"
                     "${POCO_LIB_DIR}/libPocoXMLd.so"
                     "${POCO_LIB_DIR}/libPocoFoundationd.so"
)

set(SYSTEM_LIBS pthread)
set(LIBS astlib ${POCO_LIBS} ${SYSTEM_LIBS})

include_directories(${POCO_INCLUDE_DIR})

add_subdirectory(astlib obj/astlib)

add_executable(loader src/loader.cpp)
target_link_libraries(loader ${LIBS})

