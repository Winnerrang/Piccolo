set(lua_SOURCE_DIR_ ${CMAKE_CURRENT_SOURCE_DIR}/lua-5.4.6)

file(GLOB lua_src ${lua_SOURCE_DIR_}/*.c)

# add the library
add_library(lua_static STATIC ${lua_src})

list (REMOVE_ITEM lua_src 
${lua_SOURCE_DIR_}/lua.c 
${lua_SOURCE_DIR_}/ltests.c 
${lua_SOURCE_DIR_}/onelua.c )

# include the header files
target_include_directories(lua_static PUBLIC ${lua_SOURCE_DIR_})