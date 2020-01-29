############
# asp_test #
############
list(APPEND asptest_features cxx_std_14 )

list(APPEND asptest_files "test_set.h")

#list(APPEND asptest_compile_opt "-Winline")

message("Target: asptest")
add_library( asptest INTERFACE )
target_sources( asptest INTERFACE ${asptest_files} )
target_compile_features(asptest INTERFACE ${asptest_features} )
#target_compile_options(asptest INTERFACE ${asptest_compile_opt} )
target_include_directories(asptest INTERFACE ${CMAKE_CURRENT_LIST_DIR})
