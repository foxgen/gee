# build main application
add_executable(genchess 
	main.cpp
)
target_link_libraries(genchess
	genchesslib
)
add_dependencies(genchess genchesslib)