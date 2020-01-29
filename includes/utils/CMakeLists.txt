#########
# utils #
#########
message("Target: utils")
add_library( utils INTERFACE )
target_sources( utils INTERFACE utils.h )
target_compile_features(utils INTERFACE cxx_constexpr )

