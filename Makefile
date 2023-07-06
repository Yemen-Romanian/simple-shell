INC=-I./include
CC=gcc
TARGET_NAME=lsh

all:
	$(CC) $(INC) -o $(TARGET_NAME) src/builtins.c src/parser.c src/processes.c src/main.c
