find_package(Poco 1.7.0 REQUIRED COMPONENTS Foundation JSON XML CONFIG PATHS "/opt/rsys/platform" "d:/opt/rsys/platform")
include_directories(${PocoFoundation_INCLUDE_DIRECTORIES})

add_executable(generator GeneratedTypes.cpp PrimitiveItem.cpp model/BitsDescription.cpp bootstrap/generate_symbols.cpp)    
target_link_libraries(generator ${Poco_LIBRARIES} ${SYSTEM_LIBS})


# add the command to generate the source code
set(GENERATED_MODULE "${CMAKE_CURRENT_SOURCE_DIR}/AsterixItemDictionary")
set(GENERATED_SOURCE "${GENERATED_MODULE}.cpp")
set(XML_SPECS_DIR "${CMAKE_SOURCE_DIR}/specs")

# Zoznam XML ako zavislost pre rebuild src
file(GLOB XML_SPECS_FILES "${XML_SPECS_DIR}/*.xml")
add_custom_command(OUTPUT ${GENERATED_SOURCE} PRE_BUILD COMMAND generator ${XML_SPECS_DIR} ${GENERATED_MODULE} DEPENDS generator ${XML_SPECS_FILES})
  
include_directories(. ${CMAKE_CURRENT_BINARY_DIR})

set(srcs ${GENERATED_SOURCE})
aux_source_directory(. srcs)
aux_source_directory(model srcs)
aux_source_directory(decoder srcs)
aux_source_directory(encoder srcs)

add_library(astlib SHARED ${srcs})

set(LIBVER "0.9.0")
target_link_libraries(astlib ${Poco_LIBRARIES})
set_target_properties(astlib PROPERTIES VERSION ${LIBVER} SOVERSION ${LIBVER} DEFINE_SYMBOL ASTLIB_EXPORTS)
target_compile_definitions(astlib PRIVATE "-DASTLIB_DLL")

    INSTALL(DIRECTORY .
        DESTINATION include/astlib
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN ".svn" EXCLUDE)

    INSTALL(TARGETS astlib
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
