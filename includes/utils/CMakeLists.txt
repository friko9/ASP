#########
# utils #
#########
list(APPEND utils_features cxx_std_14 )
list(APPEND utils_features cxx_constexpr )
list(APPEND utils_features cxx_relaxed_constexpr )

list(APPEND utils_files "utils.h")

list(APPEND utils_compile_opt "-Winline")

message("Target: utils")
add_library( utils INTERFACE )
target_sources( utils INTERFACE ${utils_files} )
target_compile_features(utils INTERFACE ${utils_features} )
target_compile_options(utils INTERFACE ${utils_compile_opt} )
target_include_directories(utils INTERFACE ${CMAKE_CURRENT_LIST_DIR})
