cmake_minimum_required(VERSION 3.0)

project (gee)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB genchesslib_SRC
	"${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

add_library(genchesslib 
	${genchesslib_SRC}
)

add_subdirectory(gee)
add_subdirectory(test)