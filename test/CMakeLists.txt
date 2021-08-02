# build tests
add_executable(test
	test.cpp
)

set (GTEST_DIR ../../googletest)

target_include_directories(test PUBLIC
	${GTEST_DIR}/googletest/include
)

target_link_directories(test PRIVATE
	${GTEST_DIR}/build/lib
)

target_link_libraries(test
	genchesslib
	-lgtest 
	-lgtest_main
)
add_dependencies(test genchesslib)