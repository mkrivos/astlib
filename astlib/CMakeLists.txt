find_package(Poco 1.7.0 REQUIRED COMPONENTS Foundation XML CONFIG PATHS "/opt/rsys/platform" "d:/opt/rsys/platform")
include_directories(${PocoFoundation_INCLUDE_DIRECTORIES})

include_directories(.)
aux_source_directory(. srcs)
aux_source_directory(model srcs)
aux_source_directory(decoder srcs)

add_library(astlib ${srcs})
target_link_libraries(astlib ${Poco_LIBRARIES})

