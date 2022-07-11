# ARGS and SNIPPET are environment variables.

CC   := gcc
EXE  := ./bin/$(SNIPPET).exe
SRC  := $(SNIPPET).c

LIBS := -L../bin -lcascade
INC  := -I../include
DBG  := -g
OPS  := # -O2
ADD  := -Wall

$(EXE): $(SRC)
	@echo Compiling...
	@$(CC) $^ -o $@ $(LIBS) $(INC) $(DBG) $(OPS)
	@echo Compiled.

.PHONY: run
run: $(EXE)
	@$(EXE) $(ARGS)

.PHONY: clean
clean:
	@echo Cleaning...
	@del /S /Q .\bin\*
	@echo Cleaned.

.PHONY: debug
debug: $(EXE)
	@gdb --args $(EXE) $(ARGS)