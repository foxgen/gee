cmake_minimum_required(VERSION 3.0)

project (gee)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

add_executable(genchess 
		${SOURCES}
		${HEADERS}
		)



