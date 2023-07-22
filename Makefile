INC=-I./include
SRC=src/*.c
CC=gcc
TARGET_NAME=lsh

all:
	$(CC) -g $(INC) -o $(TARGET_NAME) $(SRC)
