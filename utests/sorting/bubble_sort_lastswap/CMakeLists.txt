######################################
# utest/sorting/bubble_sort_lastswap #
######################################
list(APPEND depends aspsorting)
list(APPEND features cxx_std_14 )
list(APPEND compile_opt "-Wall")

list(APPEND files "bubble_sort_lastswap.cpp")

message("Target: gtest_bubble_sort_lastswap")
add_executable( gtest_bubble_sort_lastswap )
target_sources( gtest_bubble_sort_lastswap PRIVATE ${files} )
target_compile_features(gtest_bubble_sort_lastswap PRIVATE ${features} )
target_compile_options(gtest_bubble_sort_lastswap PRIVATE ${compile_opt} )
target_link_libraries(gtest_bubble_sort_lastswap PRIVATE ${depends} GTest::GTest GTest::Main)

gtest_discover_tests(gtest_bubble_sort_lastswap)

#########
# clean #
#########
unset(files)
unset(depends)
unset(features)
unset(compile_opt)
