########################
# utest/lists/list_stl #
########################
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

#####################
# list_stl/contains #
#####################
list(APPEND files_short "list_stl_empty.cpp")
list(APPEND files_short "list_stl_insert_short.cpp")
list(APPEND files_short "list_stl_remove_short.cpp")
list(APPEND files_long "list_stl_insert_long.cpp")
list(APPEND files_long "list_stl_remove_long.cpp")
list(APPEND depends asplists)
list(APPEND depends utest_includes)
add_google_test(FNAME "list_stl" LABEL "interface_short" DEPENDS ${depends} FILES ${files_short} )
add_google_test(FNAME "list_stl" LABEL "interface_long" DEPENDS ${depends} FILES ${files_long} )

########
# rest #
########
list(APPEND files "list_stl_test_find.cpp")
list(APPEND files "list_stl_test.h")
list(APPEND files "list_stl_test_insert.cpp")
#list(APPEND files "list_stl_test_remove.cpp")
