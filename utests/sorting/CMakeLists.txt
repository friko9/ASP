#################
# utest/sorting #
#################
add_subdirectory( ./bubble_sort_lastswap )

list(APPEND depends aspsorting )
list(APPEND features cxx_std_14 )
list(APPEND compile_opt "-Wall")

#################
# utest_sorting #
#################
list(APPEND files "bubble_sort_lastswap.cpp")
list(APPEND files "bubble_sort_simple.cpp")
list(APPEND files "counting_sort_stlmap.cpp")
list(APPEND files "heapsort.cpp")
list(APPEND files "insertion_sort_index_bitand.cpp")
list(APPEND files "insertion_sort_index.cpp")
list(APPEND files "insertion_sort_index_warden.cpp")
list(APPEND files "insertion_sort_iter_bitand.cpp")
list(APPEND files "insertion_sort_iter_bitand_mem.cpp")
list(APPEND files "insertion_sort_iter.cpp")
list(APPEND files "insertion_sort_iter_warden.cpp")
list(APPEND files "insertion_sort_iter_warden_mem.cpp")
list(APPEND files "mergesort.cpp")
list(APPEND files "quicksort.cpp")
list(APPEND files "quicksort_enchanced.cpp")
list(APPEND files "quicksort_enchanced_indexing.cpp")
list(APPEND files "quicksort_enchanced_looped.cpp")
list(APPEND files "selection_sort_index.cpp")
list(APPEND files "selection_sort_iter.cpp")
list(APPEND files "selection_sort_stlmin.cpp")
list(APPEND files "shake_sort_lastswap.cpp")
list(APPEND files "shell_sort.cpp")
list(APPEND files "sorting.cpp")
list(APPEND files "sorting.h")
list(APPEND files "stl_qsort_1.cpp")
list(APPEND files "stl_qsort_2.cpp")
list(APPEND files "stl_sort.cpp")
list(APPEND files "stl_sort_indexing.cpp")
list(APPEND files "stl_stable_sort.cpp")

message("Target: utest_sorting")
add_executable( utest_sorting )
target_sources( utest_sorting PRIVATE ${files} )
target_compile_features(utest_sorting PRIVATE ${features} )
target_compile_options(utest_sorting INTERFACE ${compile_opt} )
target_link_libraries(utest_sorting PRIVATE ${depends} asptest)
set_target_properties(utest_sorting PROPERTIES LINKER_LANGUAGE CXX)

add_test(NAME utest-sorting COMMAND "$<TARGET_FILE:utest_sorting>")

#########
# clean #
#########
unset(files)
unset(depends)
unset(features)
unset(compile_opt)
