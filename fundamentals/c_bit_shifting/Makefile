# build here
CC = gcc
FLAGS = -Wall -std=c11 -o
EXK = potatoe
SRC = main.c
OUTP = outputz.txt

raw :
	clear
	rm -f $(EXK)
	$(CC) $(FLAGS) $(EXK) $(SRC)
	@echo "[ $(EXK) ] is compiled and ready to run"

clean :
	clear
	rm -f $(EXK)
	rm -f $(OUTP)
	@echo "executable and outputs were deleted"
