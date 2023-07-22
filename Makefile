INC=-I./include
CC=gcc
TARGET_NAME=lsh

all:
	$(CC) -g $(INC) -o $(TARGET_NAME) src/builtins.c src/parser.c src/processes.c src/utils.c src/main.c
