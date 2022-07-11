# ARGS is an environment variable.

CC   := gcc
AR   := ar
SRC  := $(shell dir /S /B .\src\*.c)
OUT  := ./bin/libcascade.a

LIBS := -L./vendor
INC  := -I./vendor
DBG  := -g
OPS  := # -O2
ADD  := -Wall

$(OUT): $(SRC)
	@echo Compiling...
	@$(CC) -c $^ $(LIBS) $(INC) $(DBG) $(OPS) $(ADD)
	@$(AR) rcs $@ *.o
	@del /S /Q *.o
	@echo Compiled.

.PHONY: clean
clean:
	@echo Cleaning...
	@del /S /Q .\bin\*
	@echo Cleaned.