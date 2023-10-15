HEADER_FILES = $(wildcard ../headers/*.h)
SRC_FILES = $(wildcard ../src/*.cpp)

main: Makefile main.cpp $(HEADER_FILES) $(SRC_FILES)
	g++ -DWSL -DASIO_STANDALONE -Wall -Wextra -Werror -Wno-error=unused-parameter -Wno-error=unused-variable -std=c++17 -I/home/poold/canvas++/headers -I/home/poold/canvas++/libs/asio/include -I/home/poold/canvas++/libs/json/include -I/home/poold/canvas++/libs/websocketpp $(SRC_FILES) main.cpp -o main -lpthread