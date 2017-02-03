include_directories(.)
aux_source_directory (. srcs)
aux_source_directory (model srcs)
add_library (astlib ${srcs})

