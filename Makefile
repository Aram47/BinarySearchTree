G++ = g++
FILES = main.cpp
EXE = BTS
DEL = rm

all:
	$(G++) $(FILES) -o $(EXE)
del:
	$(DEL) $(EXE)