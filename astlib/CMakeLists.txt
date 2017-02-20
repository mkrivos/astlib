find_package(Poco 1.7.0 REQUIRED COMPONENTS Foundation JSON XML CONFIG PATHS "/opt/rsys/platform" "d:/opt/rsys/platform")
include_directories(${PocoFoundation_INCLUDE_DIRECTORIES})

add_executable(generator GeneratedTypes.cpp PrimitiveItem.cpp model/BitsDescription.cpp bootstrap/generate_symbols.cpp)    
target_link_libraries(generator ${Poco_LIBRARIES} ${SYSTEM_LIBS})


# add the command to generate the source code
set(GENERATED_MODULE "AsterixItemDictionary")
set(GENERATED_SOURCE "${GENERATED_MODULE}.cpp")

add_custom_command(OUTPUT ${GENERATED_SOURCE} PRE_BUILD COMMAND generator "${CMAKE_SOURCE_DIR}/specs" ${GENERATED_FILE} DEPENDS generator)
  
include_directories(. ${CMAKE_CURRENT_BINARY_DIR})

set(srcs ${GENERATED_SOURCE})
aux_source_directory(. srcs)
aux_source_directory(model srcs)
aux_source_directory(decoder srcs)
aux_source_directory(encoder srcs)

add_library(astlib ${srcs})
target_link_libraries(astlib ${Poco_LIBRARIES})

