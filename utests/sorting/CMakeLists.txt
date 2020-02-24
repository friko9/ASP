#################
# utest/sorting #
#################
function(add_sorting_function_test_helper)
  cmake_parse_arguments(add_sorting_function_test_helper "" "FNAME;LABEL" "FILES" ${ARGN})
  set(fname ${add_sorting_function_test_helper_FNAME})
  set(label ${add_sorting_function_test_helper_LABEL})
  set(files ${add_sorting_function_test_helper_FILES})
  set(name utest_${label}_${fname})

  list(APPEND depends aspsorting utest_includes)
  list(APPEND features cxx_std_14 )
  list(APPEND compile_opt "-Wall")

  message("Target: ${name}")
  add_executable( ${name} )
  target_sources( ${name} PRIVATE ${files}  )
  target_compile_features( ${name} PRIVATE ${features} )
  target_compile_options( ${name} PRIVATE ${compile_opt} )
  target_compile_definitions( ${name} PRIVATE -DUTEST_FNAME=${fname} )
  target_include_directories( ${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries( ${name} PRIVATE ${depends} GTest::GTest GTest::Main)

  gtest_discover_tests( ${name}
    TEST_PREFIX "${name}_"
    PROPERTIES LABELS ${label} )
endfunction()

function(add_sorting_function_test fname)
  list(APPEND files_short "../test_boundries.cpp")
  list(APPEND files_short "../test_combinations.cpp")
  list(APPEND files_long "../test_largeset.cpp")
  add_sorting_function_test_helper(FNAME ${fname} LABEL "interface_short" FILES ${files_short} )
  add_sorting_function_test_helper(FNAME ${fname} LABEL "interface_long"  FILES ${files_long} )
endfunction()

# Include targets with tests
add_subdirectory(bubble_sort)
add_subdirectory(insertion_sort)
add_subdirectory(misc_sort)
add_subdirectory(quick_sort)
add_subdirectory(selection_sort)
add_subdirectory(stl_sort)
