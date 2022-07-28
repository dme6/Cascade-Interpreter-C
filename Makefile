# ARGS is an environment variable.

# TODO: Combine makefiles for simplicity.

CC   := gcc
AR   := ar
SRC  := $(shell dir /S /B .\src\*.c)
OUT  := ./bin/libcascade.a

DBG  := -g
OPS  := # -O2
ADD  := -Wall

$(OUT): $(SRC)
	@echo Compiling...
	@$(CC) -c $^ $(DBG) $(OPS) $(ADD)
	@$(AR) rcs $@ *.o
	@del /S /Q *.o
	@echo Compiled.

.PHONY: clean
clean:
	@echo Cleaning...
	@del /S /Q .\bin\*
	@echo Cleaned.