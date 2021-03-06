EXE = program.exe
CC = gcc

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS += -Iinclude
CFLAGS += -g -Wall
#LDLIBS +=

.PHONY: all clean

all: $(EXE)

$(EXE):$(OBJ)
	$(CC) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)