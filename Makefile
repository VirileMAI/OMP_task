TARGET = Bookstore
CC = g++
SRC = Bookstore.cpp

all: clean $(TARGET)

$(TARGET): $(SRC)
	$(CC) $< -o $@

clean:
	rm -rf $(TARGET)

format:
	clang-format -i $(SRC)