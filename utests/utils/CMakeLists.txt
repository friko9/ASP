###############
# utest/utils #
###############
list(APPEND utest_utils_features cxx_std_14 )

list(APPEND utest_utils_files "utils.cpp")

#list(APPEND utest_utils_compile_opt "Winline")

message("Target: utest_utils")
add_executable( utest_utils )
target_sources( utest_utils PRIVATE ${utest_utils_files} )
target_compile_features(utest_utils PRIVATE ${utest_utils_features} )
#target_compile_options(utils INTERFACE ${utest_utils_compile_opt} )

target_link_libraries(utest_utils PRIVATE utils) #test_set
set_target_properties(utest_utils PROPERTIES LINKER_LANGUAGE CXX)

unset(utest_utils_features)
unset(utest_utils_files)
unset(utest_utils_compile_opt)

add_test(NAME utest-utils COMMAND "$<TARGET_FILE:utest_utils>")
