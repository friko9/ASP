###############
# asp_sorting #
###############
list(APPEND aspsorting_features cxx_std_14 )

list(APPEND aspsorting_files "bubble_sort.h")
list(APPEND aspsorting_files "insertion_sort.h")
list(APPEND aspsorting_files "misc_sort.h")
list(APPEND aspsorting_files "quick_sort.h")
list(APPEND aspsorting_files "selection_sort.h")
list(APPEND aspsorting_files "stl_sort.h")

#list(APPEND aspsorting_compile_opt "-Winline")

message("Target: aspsorting")
add_library( aspsorting INTERFACE )
target_sources( aspsorting INTERFACE ${aspsorting_files} )
target_compile_features(aspsorting INTERFACE ${aspsorting_features} )
#target_compile_options(aspsorting INTERFACE ${aspsorting_compile_opt} )
target_include_directories(aspsorting INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
