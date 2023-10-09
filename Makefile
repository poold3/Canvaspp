H_FILES = $(wildcard headers/*.h)
SRC_FILES = $(wildcard src/*.cpp)

main: $(H_FILES) $(SRC_FILES) main.cpp Makefile
	g++ -DASIO_STANDALONE -Wall -Wextra -Werror -Wno-error=unused-parameter -Wno-error=unused-variable -std=c++11 -I/home/poold/canvas++/headers -I/home/poold/canvas++/libs/websocketpp -I/home/poold/canvas++/libs/asio/include -I/home/poold/canvas++/libs/json/include $(SRC_FILES) main.cpp -o main -lpthread