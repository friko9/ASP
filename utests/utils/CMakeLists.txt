###############
# utest/utils #
###############
list(APPEND depends utils)
list(APPEND features cxx_std_14 )
list(APPEND compile_opt "-Wall")

###############
# gtest_utils #
###############
list(APPEND files "gtest_utils.cpp")

message("Target: gtest_utils")
add_executable( gtest_utils )
target_sources( gtest_utils PRIVATE ${files} )
target_compile_features(gtest_utils PRIVATE ${features} )
target_compile_options(gtest_utils PRIVATE ${compile_opt} )
target_link_libraries(gtest_utils PRIVATE ${depends} GTest::GTest GTest::Main)

gtest_discover_tests(gtest_utils)

#########
# clean #
#########
unset(files)
unset(depends)
unset(features)
unset(compile_opt)
