H_FILES = $(wildcard headers/*.h) $(wildcard headers/input/*.h) $(wildcard headers/output/*.h)
SRC_FILES = $(wildcard src/*.cpp) $(wildcard src/input/*.cpp) $(wildcard src/output/*.cpp)

main: $(H_FILES) $(SRC_FILES) main.cpp Makefile
	g++ -Wall -Wextra -Werror -Wno-error=unused-parameter -Wno-error=unused-variable -std=c++11 -I/home/poold/canvas++/headers -I/home/poold/canvas++/libs/websocketpp -I/home/poold/canvas++/libs/boost -I/home/poold/canvas++/libs/json/include $(SRC_FILES) main.cpp -o main -lpthread