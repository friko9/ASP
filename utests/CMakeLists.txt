###################
# Add Google Test #
###################
function(add_google_test)
  cmake_parse_arguments(add_google_test "" "FNAME;LABEL;TIMEOUT" "DEPENDS;FILES" ${ARGN})
  set(fname ${add_google_test_FNAME})
  set(label ${add_google_test_LABEL})
  set(timeout ${add_google_test_TIMEOUT})
  if(NOT ${timeout})
    set(timeout 5)
  endif()
  set(files ${add_google_test_FILES})
  set(depends ${add_google_test_DEPENDS})
  set(name utest_${label}_${fname})

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
    PROPERTIES LABELS "${label}"
    DISCOVERY_TIMEOUT ${timeout} )
endfunction()

##########
# utests #
##########
add_subdirectory(hashsets)
add_subdirectory(lists)
add_subdirectory(sorting)
add_subdirectory(treesets)
add_subdirectory(utils)

################
# GOOGLE TESTS #
################
add_subdirectory(includes)
add_subdirectory(asp_lists)
add_subdirectory(asp_treesets)
