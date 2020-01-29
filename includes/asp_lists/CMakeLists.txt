#############
# asp_lists #
#############
list(APPEND asplists_features cxx_std_14 )

list(APPEND asplists_files "list_array_enchanced.h")
list(APPEND asplists_files "list_array.h")
list(APPEND asplists_files "list_array_selforganizing.h")
list(APPEND asplists_files "list_array_sorted.h")
list(APPEND asplists_files "list_array_sorted_warden.h")
list(APPEND asplists_files "list_dynamic.h")
list(APPEND asplists_files "list_stlforward.h")
list(APPEND asplists_files "list_stl.h")

#list(APPEND asplists_compile_opt "-Winline")

message("Target: asplists")
add_library( asplists INTERFACE )
target_sources( asplists INTERFACE ${asplists_files} )
target_compile_features(asplists INTERFACE ${asplists_features} )
#target_compile_options(asplists INTERFACE ${asplists_compile_opt} )
target_include_directories(asplists INTERFACE ${CMAKE_CURRENT_LIST_DIR})
