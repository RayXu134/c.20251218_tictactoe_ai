# tictactoe/Makefile
# Copyright (c) 2025 Ray. All Rights Reserved.

GCC = gcc
GCC_FLAGS = -lncurses
SOURCE = main.c
TARGET = main

$(TARGET): $(SOURCE)
	$(GCC) $(SOURCE) -o $(TARGET) $(GCC_FLAGS)

clean:
	rm -f $(TARGET)