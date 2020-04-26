################
# Google Tests #
# asp_hashsets #
################
list(APPEND depends asphashsets)
list(APPEND depends utest_includes)

list(APPEND files "utest_hashset.h")
list(APPEND files_short "empty_short.cpp")
list(APPEND files_short "insert_short.cpp")
list(APPEND files_short "remove_short.cpp")
list(APPEND files_short ${files})
list(APPEND files_long "insert_long.cpp")
list(APPEND files_long "remove_long.cpp")
list(APPEND files_long ${files})

add_google_test(FNAME "hashsets" LABEL "interface_short" DEPENDS ${depends} FILES ${files_short} )
add_google_test(FNAME "hashsets" LABEL "interface_long" DEPENDS ${depends} FILES ${files_long} )
