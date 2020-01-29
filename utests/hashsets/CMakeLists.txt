##################
# utests/hashset #
##################
list(APPEND utest_hashsets_features cxx_std_14 )

list(APPEND utest_hashsets_files "hashset_array_test_contains.cpp")
#list(APPEND utest_hashsets_files "hashset_array_test_exclude_elem.cpp") Test needs correction
list(APPEND utest_hashsets_files "hashset_array_test_find.cpp")
list(APPEND utest_hashsets_files "hashset_array_test.h")
list(APPEND utest_hashsets_files "hashset_array_test_insert.cpp")
list(APPEND utest_hashsets_files "hashset_array_test_insert_hash.cpp")
#list(APPEND utest_hashsets_files "hashset_array_test_move_elem.cpp") Test needs correction
list(APPEND utest_hashsets_files "hashset_array_test_remove.cpp")
list(APPEND utest_hashsets_files "hashset_array_test_resize.cpp")
list(APPEND utest_hashsets_files "hashset_bucket_test_contains.cpp")
list(APPEND utest_hashsets_files "hashset_bucket_test_find.cpp")
list(APPEND utest_hashsets_files "hashset_bucket_test.h")
list(APPEND utest_hashsets_files "hashset_bucket_test_insert.cpp")
list(APPEND utest_hashsets_files "hashset_bucket_test_remove.cpp")
list(APPEND utest_hashsets_files "hashset_bucket_test_resize.cpp")
list(APPEND utest_hashsets_files "hashsets.cpp")
list(APPEND utest_hashsets_files "hashset_stl_test_contains.cpp")
list(APPEND utest_hashsets_files "hashset_stl_test.h")
list(APPEND utest_hashsets_files "hashset_stl_test_insert.cpp")
list(APPEND utest_hashsets_files "hashset_stl_test_remove.cpp")

#list(APPEND utest_hashsets_compile_opt "-Winline")

message("Target: utest_hashsets")
add_executable( utest_hashsets )
target_sources( utest_hashsets PRIVATE ${utest_hashsets_files} )
target_compile_features(utest_hashsets PRIVATE ${utest_hashsets_features} )
#target_compile_options(hashsets INTERFACE ${utest_hashsets_compile_opt} )

target_link_libraries(utest_hashsets PRIVATE asphashsets asptest)
set_target_properties(utest_hashsets PROPERTIES LINKER_LANGUAGE CXX)

unset(utest_hashsets_features)
unset(utest_hashsets_files)
unset(utest_hashsets_compile_opt)

add_test(NAME utest-hashsets COMMAND "$<TARGET_FILE:utest_hashsets>")

