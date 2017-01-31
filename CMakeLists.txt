project (astlib)
cmake_minimum_required(VERSION 3.3)

include_directories(.)

SET(SYSTEM_LIBS
)

SET(LIBS
    astlib
    ${SYSTEM_LIBS}    
)

add_subdirectory(astlib obj/astlib)

add_executable(loader src/loader.cpp)
target_link_libraries(loader ${LIBS})