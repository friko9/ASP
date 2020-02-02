###############
# utest/utils #
###############
list(APPEND depends utils)
list(APPEND features cxx_std_14 )
list(APPEND compile_opt "-Wall")

###############
# utest_utils #
###############
list(APPEND files "utils.cpp")

message("Target: utest_utils")
add_executable( utest_utils )
target_sources( utest_utils PRIVATE ${files} )
target_compile_features(utest_utils PRIVATE ${features} )
target_compile_options(utest_utils PRIVATE ${compile_opt} )
target_link_libraries(utest_utils PRIVATE ${depends} asptest)
set_target_properties(utest_utils PROPERTIES LINKER_LANGUAGE CXX)

#add_test(NAME utest-utils COMMAND "$<TARGET_FILE:utest_utils>")

###############
# gtest_utils #
###############
list(APPEND files "utils.cpp")

message("Target: gtest_utils")
add_executable( gtest_utils )
target_sources( gtest_utils PRIVATE "gtest_utils.cpp" )
target_compile_features(gtest_utils PRIVATE ${features} )
target_compile_options(gtest_utils PRIVATE ${compile_opt} )
target_include_directories(gtest_utils PRIVATE "../../includes/utils")
target_link_libraries(gtest_utils PRIVATE ${depends} GTest::GTest GTest::Main)

gtest_discover_tests(gtest_utils DISCOVERY_TIMEOUT 100)

#########
# clean #
#########
unset(files)
unset(depends)
unset(features)
unset(compile_opt)
