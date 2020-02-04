######################################
# utest/sorting/bubble_sort_lastswap #
######################################
set(name utest_bubble_sort_lastswap)

list(APPEND depends aspsorting utest_includes)
list(APPEND features cxx_std_14 )
list(APPEND compile_opt "-Wall")

list(APPEND files "./test_boundries.cpp")
list(APPEND files "./test_combinations.cpp")

message("Target: ${name}")
add_executable( ${name} )
target_sources( ${name} PRIVATE ${files} )
target_compile_features( ${name} PRIVATE ${features} )
target_compile_options( ${name} PRIVATE ${compile_opt} )
target_link_libraries( ${name} PRIVATE ${depends} GTest::GTest GTest::Main)

gtest_discover_tests( ${name} TEST_PREFIX "${name}_" )

#########
# clean #
#########
unset(files)
unset(depends)
unset(features)
unset(compile_opt)
unset(name)
