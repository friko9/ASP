cmake_minimum_required( VERSION 3.13.4 FATAL_ERROR )

macro(version_not_found)
  message(SEND_ERROR "No project version could be determined.")
  message(FATAL_ERROR "Set project version manually by: cmake -D version=v1.2.3")
endmacro()

option(version "Project version")

set(commit_hash "nohash")

if(NOT version)
find_package(Git)
  if(NOT Git_FOUND)
    message(SEND_ERROR "Git not found.")
    version_not_found()
  endif()

  execute_process( COMMAND "${GIT_EXECUTABLE}" describe --tags
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    RESULT_VARIABLE result
    OUTPUT_VARIABLE version
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

  if( NOT result EQUAL 0 )
    message(SEND_ERROR "Could not get project version from git control system.")
    version_not_found()
  endif()
  unset(result)
endif()

set(v_major 0)
set(v_minor 0)
set(v_patch 0)
set(v_desc "nohash")
set(version_regexp "^v([0-9]+)(\.([0-9]+))?([.-]([0-9]+))?[-.]?(.*)?$")
if( version MATCHES ${version_regexp})
  set(v_major "${CMAKE_MATCH_1}")
  if(CMAKE_MATCH_3)
    set(v_minor "${CMAKE_MATCH_3}")
  endif()
  if(CMAKE_MATCH_5)
    set(v_patch "${CMAKE_MATCH_5}")
  endif()
  if(CMAKE_MATCH_6)
    set(v_desc "${CMAKE_MATCH_6}")
  endif()
else()
  message(SEND_ERROR "version '${version}' not matching regexp: ${version_regexp}")
  version_not_found()
endif()

message("Project version is: ${v_major}.${v_minor}.${v_patch}")
if(v_desc)
  message("Commit hash is: ${v_desc}")
else()
  message("No commit hash defined")
endif()

project( ASP VERSION ${v_major}.${v_minor}.${v_patch} LANGUAGES CXX ) # HOMEPAGE, DESCRIPTION 

include_directories(${CMAKE_CURRENT_SOURCE_DIR}) #TODO: remove after include paths carried in dependencies

add_subdirectory(includes)
#add_subdirectory(itests)
#add_subdirectory(perf_tests)
enable_testing()
add_subdirectory(utests)
