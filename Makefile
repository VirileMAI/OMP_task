TARGET = Bookstore
CC = g++
SRC = Bookstore.cpp func.cpp class.cpp

all: clean $(TARGET)

$(TARGET): $(SRC)
	$(CC) $^ -o $@

clean:
	rm -rf $(TARGET)

format:
	clang-format -i *.cpp