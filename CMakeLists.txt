cmake_minimum_required( VERSION 3.5 )
project( Simple_Server )

# set flags and module path
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
add_executable( server server.cc )
