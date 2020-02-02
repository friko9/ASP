cmake_minimum_required( VERSION 3.13.4 FATAL_ERROR )

option(version "Project version")

include(${CMAKE_CURRENT_LIST_DIR}/cmake_scripts/Version.cmake)

if(NOT version)
  git_tag_desc(version)
else()
  message(WARNING "Project version defined manually."
  "To return to automatic version detection reset CMake cache.\n"
  "If using out-of-source build remove build directory with 'rm -r ./build/'\n"
  "If using git version control system remove all untracked files with 'git clean -d -f -x -n'")
endif()

parse_version(version ${version})
if(NOT version_FOUND)
  message(SEND_ERROR "No project version could be obtained reading git signed tags.")
  message(FATAL_ERROR "Set project version manually by: cmake -D version=v1.2.3-description")
endif()

message("Project version is: ${version_major}.${version_minor}.${version_patch}")
message("Version description: ${version_desc}")
project( ASP VERSION ${version_major}.${version_minor}.${version_patch} LANGUAGES CXX ) # HOMEPAGE, DESCRIPTION 

include_directories(${CMAKE_CURRENT_SOURCE_DIR}) #TODO: remove after include paths carried in dependencies
message("----------Enter Subdirectories----------")
add_subdirectory(includes)
#add_subdirectory(itests)
#add_subdirectory(perf_tests)
enable_testing()
add_subdirectory(utests)
