CC = gcc
CFLAGS = -c -Wall -Werror -Iinclude
LDFLAGS =

ODIR = obj
BDIR = bin

SRC = $(shell find src -iname "*.c")
OBJ = $(SRC:.c=.o)
BIN = aclsim

all: $(SRC) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@
	mkdir -p $(BDIR)
	mkdir -p $(ODIR)
	mv $(BIN) $(BDIR)
	mv $(OBJ) $(ODIR)
	@echo finished successfully!
.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf bin
	rm -rf obj
	rm -f $(OBJ)
	@echo cleaned successfully!

.phony: clean
