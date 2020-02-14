########################################################################################
# function: git_tag_desc							       #
# 										       #
# inputs:									       #
# <result_var> prefix of the output variables					       #
# 										       #
# outputs:									       #
# <result_var> updated if version found						       #
# 										       #
# required packages:								       #
# Git										       #
# 										       #
# env. requirements:								       #
# Version is kept in signed tags in git version control system                         #
# Calling ""${GIT_EXECUTABLE}" describe --tags" returns value and exit with no error   #
# 										       #
# Failure strategy:                                                                    #
# In case of failure outputs remain uchanged                                           #
########################################################################################

function(git_tag_desc result_var)
  find_package(Git)

  if(NOT Git_FOUND)
    message(SEND_ERROR "Git not found.")
    return()
  endif()

  execute_process( COMMAND "${GIT_EXECUTABLE}" describe --tags --long
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    RESULT_VARIABLE result
    OUTPUT_VARIABLE tag_desc
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

  if( NOT result EQUAL 0 )
    message(SEND_ERROR "Could not get project version from git control system.")
    return()
  endif()
  
  set(${result_var} ${tag_desc} PARENT_SCOPE)
endfunction()

##########################################################################################################
# function: git_parse_version 										 #
# 													 #
# inputs:												 #
# <result_prefix> prefix of the output variables							 #
# <parsed_str>    string to be parsed									 #
# 													 #
# outputs:												 #
# <${result_prefix}_FOUND> 1 if <parsed_str> matches regexp, not defined otherwise			 #
# <${result_prefix}_major> major version number (first detected decimal number)				 #
# <${result_prefix}_minor> minor version number (second detected decimal number)			 #
# <${result_prefix}_patch> patch version number (third detected decimal number)				 #
# <${result_prefix}_desc>  trailing version description (alphanumeric string after third decimal number) #
# 													 #
# arg. requirements:											 #
# <parsed_str> must match <version_regexp> defined in function body					 #
# it must be a set of 1-3 numbers separated by a single non-numbers					 #
# it may start with nonnumbers										 #
# 													 #
# failure strategy:											 #
# In case a value cannot be obtained when matching regex default value is assigned:			 #
# 0 for <${result_prefix}_major>, <${result_prefix}_minor>, <${result_prefix}_patch>			 #
# "" for <${result_prefix}_desc>									 #
##########################################################################################################

function(parse_version result_prefix parsed_str)
  set(version_regexp "^v([0-9]+)(\.([0-9]+))?([.-]([0-9]+))?[-.]?(.*)?$")
  set(version_regexp "^[^0-9]*([0-9]+)([^0-9]([0-9]+))?([^0-9]([0-9]+))?[^0-9a-zA-Z]*(.*)?$")
  set(v_major 0)
  set(v_minor 0)
  set(v_patch 0)
  set(v_desc "")
  if( ${parsed_str} MATCHES ${version_regexp})
    set(${result_prefix}_FOUND TRUE PARENT_SCOPE)
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
  endif()
  set(${result_prefix}_major ${v_major} PARENT_SCOPE)
  set(${result_prefix}_minor ${v_minor} PARENT_SCOPE)
  set(${result_prefix}_patch ${v_patch} PARENT_SCOPE)
  set(${result_prefix}_desc  ${v_desc}  PARENT_SCOPE)
endfunction()
