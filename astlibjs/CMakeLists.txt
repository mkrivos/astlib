cmake_minimum_required(VERSION 2.8)

# Name of the project (will be the name of the plugin)
project(addon)

#add_definitions(-DPOCO_NO_AUTOMATIC_LIBS=1)
find_package(Poco 1.7.0 REQUIRED COMPONENTS Foundation JSON XML CONFIG PATHS "/opt/rsys/platform" "d:/opt/rsys/platform")
include_directories(${PocoFoundation_INCLUDE_DIRECTORIES})

include_directories(.. . node_modules/v8pp /opt/rsys/platform/include)
link_directories(${PROJECT_NAME} ../lib ../../lib )

# Build a shared library named after the project from the files in `src/`
file(GLOB SOURCE_FILES "*.cpp" "*.h")
#set(SOURCE_FILES hello.cc)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# Gives our library file a .node extension without any "lib" prefix
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# Essential include files to build a node addon,
# You should add this line in every CMake.js based project
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})

# Essential library files to link to a node addon
# You should add this line in every CMake.js based project
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} astlib_dll ${Poco_LIBRARIES})
target_link_directories(${PROJECT_NAME} PRIVATE ../lib ../../lib )
