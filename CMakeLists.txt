project(iter)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)

add_executable(
	iter
	src/main.cpp
	src/vec.cpp
	src/iter.cpp
	src/cx.cpp
	src/func.cpp
	src/color.cpp
	src/log.cpp
)

target_link_libraries(iter Threads::Threads)

file(COPY ${CMAKE_SOURCE_DIR}/colormaps DESTINATION ${CMAKE_BINARY_DIR})
