################
# asp_hashsets #
################
list(APPEND asphashsets_features cxx_std_14 )

list(APPEND asphashsets_files "hashset_array.h")
list(APPEND asphashsets_files "hashset_bucket.h")
list(APPEND asphashsets_files "hashset_stl.h")

#list(APPEND asphashsets_compile_opt "-Winline")

message("Target: asphashsets")
add_library( asphashsets INTERFACE )
target_sources( asphashsets INTERFACE ${asphashsets_files} )
target_compile_features(asphashsets INTERFACE ${asphashsets_features} )
#target_compile_options(asphashsets INTERFACE ${asphashsets_compile_opt} )
target_include_directories(asphashsets INTERFACE ${CMAKE_CURRENT_LIST_DIR})
