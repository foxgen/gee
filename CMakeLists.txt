cmake_minimum_required(VERSION 3.0)

project (gee)

add_library(genchesslib
	game.cpp 	game.h
	move.cpp 	move.h
	position.cpp	position.h
	util.cpp	util.h
    bitboard.cpp    bitboard.h
	figure.cpp 	figure.h
	rook.cpp	rook.h
	bishop.cpp	bishop.h
	queen.cpp	queen.h
	knight.cpp	knight.h
	king.cpp	king.h
	pawn.cpp	pawn.h
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

target_include_directories(test PUBLIC
	../googletest/googletest/include
)

target_link_directories(test PRIVATE
	../googletest/build/lib
)

target_link_libraries(test
	genchesslib
	-lgtest 
	-lgtest_main
)
add_dependencies(test genchesslib)