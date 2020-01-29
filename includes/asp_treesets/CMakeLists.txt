################
# asp_treesets #
################
list(APPEND asptreesets_features cxx_std_14 )

list(APPEND asptreesets_files "treeset_array.h")
list(APPEND asptreesets_files "treeset_array_balancing.h")
list(APPEND asptreesets_files "treeset_dynamic.h")
list(APPEND asptreesets_files "treeset_dynamic_balancing.h")
list(APPEND asptreesets_files "treeset_stl.h")

#list(APPEND asptreesets_compile_opt "-Winline")

message("Target: asptreesets")
add_library( asptreesets INTERFACE )
target_sources( asptreesets INTERFACE ${asptreesets_files} )
target_compile_features(asptreesets INTERFACE ${asptreesets_features} )
#target_compile_options(asptreesets INTERFACE ${asptreesets_compile_opt} )
target_include_directories(asptreesets INTERFACE ${CMAKE_CURRENT_LIST_DIR})
