CC = g++
CFLAGS = -g -c -Wall -Werror -Isrc --std=c++11 -O3
LDFLAGS =

ODIR = obj
BDIR = bin

SRC = $(shell find src -iname "*.cpp")
OBJ = $(SRC:.cpp=.o)
BIN = aclsim

all: $(SRC) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@
	mkdir -p $(BDIR)
	mkdir -p $(ODIR)
	mv $(BIN) $(BDIR)
	mv $(OBJ) $(ODIR)
	@echo build successfully!
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf $(ODIR)
	rm -rf $(BDIR)
	@echo cleaned successfully!

.phony: clean
