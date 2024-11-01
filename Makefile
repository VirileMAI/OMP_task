TARGET = Bookstore
CC = g++
SRC = src/Bookstore.cpp src/func.cpp src/class.cpp

all: clean $(TARGET)

$(TARGET): $(SRC)
	$(CC) $^ -o $@

clean:
	rm -rf $(TARGET)

format:
	clang-format -i src/*.cpp src/*.h