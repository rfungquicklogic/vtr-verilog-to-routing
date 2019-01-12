cmake_minimum_required(VERSION 2.8.12)

project("librtlnumber")

file(GLOB_RECURSE LIB_SOURCES src/*.cpp)
file(GLOB_RECURSE LIB_HEADERS src/include/*.hpp)
files_to_dirs(LIB_HEADERS LIB_INCLUDE_DIRS)

#Create the library
add_library(librtlnumber STATIC
             ${LIB_HEADERS}
             ${LIB_SOURCES})
target_include_directories(librtlnumber PUBLIC ${LIB_INCLUDE_DIRS})
set_target_properties(librtlnumber PROPERTIES PREFIX "") #Avoid extra 'lib' prefix

#Create the test executable
target_link_libraries(librtlnumber)

install(TARGETS librtlnumber DESTINATION bin)
