
add_subdirectory(impl)
################
# Google Tests #
# asp_lists    #
################
list(APPEND depends asplists)
list(APPEND depends utest_includes)

list(APPEND files "utest_list.h")

list(APPEND files_short "empty_short.cpp")
list(APPEND files_short "insert_short.cpp")
list(APPEND files_short "remove_short.cpp")
list(APPEND files_short ${files})

list(APPEND files_long "insert_long.cpp")
list(APPEND files_long "remove_long.cpp")
list(APPEND files_long ${files})

add_google_test(FNAME "lists" LABEL "interface_short" DEPENDS ${depends} FILES ${files_short} )
add_google_test(FNAME "lists" LABEL "interface_long" DEPENDS ${depends} FILES ${files_long} )
