# This is a generic CMake setup for CGP library use
cmake_minimum_required(VERSION 3.8) 
project(cpp_files)

file(GLOB_RECURSE src_files src/*.[ch]pp)
add_executable(cpp_files ${src_files})


# Set Compiler for Unix system
if(UNIX)
   set(CMAKE_CXX_COMPILER g++)                      # Can switch to clang++ if prefered
   add_definitions(-g -O2 -std=c++14 -Wall -Wextra -Wfatal-errors -Wno-pragmas) # Can adapt compiler flags if needed
   add_definitions(-Wno-sign-compare -Wno-type-limits) # Remove some warnings
endif()

add_definitions(-DSOLUTION)

# Set Compiler for Windows/Visual Studio
if(MSVC)
   set(CMAKE_CONFIGURATION_TYPES RelWithDebInfo ) # default build as RelWithDebInfo
   set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT cpp_files ) # default project (avoids AllBuild)
   set_target_properties( cpp_files PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}$<0:> ) # default output in root dir
   set_target_properties( cpp_files PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} ) # default debug execution in root dir
   
   # Avoids the warning /W3 overided by /W4 when using Ninja
   if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
   else()
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
   endif()

    add_definitions(/MP /wd4244 /wd4127 /wd4267 /wd4706 /wd4458 /wd4996 /wd26495 /wd4305 /openmp)   # Parallel build (/MP) + disable some warnings
    source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${src_files})  #Allow to explore source directories as a tree in Visual Studio
endif()



