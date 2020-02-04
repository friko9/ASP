###############
# asp_sorting #
###############
list(APPEND features cxx_std_14 )
list(APPEND compile_opt "-Winline")

unset(depends)
foreach( name IN ITEMS bubble insertion misc quick selection stl )
  message("Target: aspsorting_${name}_sort")
  add_library( aspsorting_${name}_sort INTERFACE )
  target_sources( aspsorting_${name}_sort INTERFACE "${name}_sort.h" )
  target_compile_options(aspsorting_${name}_sort INTERFACE ${compile_opt} )
  target_compile_features(aspsorting_${name}_sort INTERFACE ${features} )
  target_include_directories(aspsorting_${name}_sort INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
  list(APPEND depends aspsorting_${name}_sort)
endforeach()
message("Target: aspsorting \t <- ${depends}")
add_library( aspsorting INTERFACE )
target_link_libraries(aspsorting INTERFACE ${depends})
