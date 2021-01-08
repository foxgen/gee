cmake_minimum_required(VERSION 3.0)

project (gee)

add_library(genchesslib
	game.cpp 
	game.h
	move.cpp 
	move.h
	position.cpp
	position.h
	types.h
)

# build main application
add_executable(genchess 
	main.cpp
)
target_link_libraries(genchess
	genchesslib
)
add_dependencies(genchess genchesslib)

# build tests
add_executable(test
	test.cpp
)
target_link_libraries(test
	genchesslib
	-lgtest -lgtest_main
)
add_dependencies(test genchesslib)