##################
# utest/includes #
##################

#list(APPEND depends )
list(APPEND features cxx_std_14 )
list(APPEND compile_opt "-Wall")

##################
# utest/includes #
##################
set(name utest_includes)

list(APPEND files "./utest_tuple.h")
list(APPEND files "./utest_utils.h")
list(APPEND files "./utest_pretty.h")
list(APPEND files "./utest_inclusive_range.h")

message("Target: ${name}")
add_library( ${name} INTERFACE )
target_sources( ${name} INTERFACE ${files} )
target_compile_features( ${name} INTERFACE ${features} )
target_compile_options( ${name} INTERFACE ${compile_opt} )

target_include_directories( ${name} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
#target_link_libraries(utest_includes INTERFACE ${depends})
