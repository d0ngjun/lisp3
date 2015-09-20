CC = g++
FLAGS = -std=c++11 -Wall -g

TARGET = lisp3
SRC_DIR = source
OBJ_DIR = object
SOURCES = $(SRC_DIR)/*.cc
OBJECTS = $(OBJ_DIR)/*.o

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJECTS)

$(OBJECTS): $(SOURCES)
	cd $(OBJ_DIR) && $(CC) $(FLAGS) -c ../$(SOURCES)

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS) core
