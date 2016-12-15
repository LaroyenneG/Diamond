OBJ := diamond.o game.o queue.o sublimeterm.o
EXENAME := diamond

CC := gcc
CFLAGS := -std=c99 -Wall -O3 -g

all : exe

exe : $(EXENAME)

$(EXENAME) : $(OBJ)
	gcc -g $^ -o $@

clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f $(EXENAME)
