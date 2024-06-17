CURSES_PATH = curses/pdcurses.a

all: clean main

main: main.o vehicle.o display.o food.o place.o ai.o
	gcc -o main main.o vehicle.o display.o $(CURSES_PATH) food.o place.o ai.o

main.o: main.c
	gcc -c -o main.o main.c

vehicle.o: vehicle.c
	gcc -c -o vehicle.o vehicle.c

display.o: display.c
	gcc -c -o display.o display.c

food.o: food.c
	gcc -c -o food.o food.c

place.o: place.c
	gcc -c -o place.o place.c

ai.o: ai.c
	gcc -c -o ai.o ai.c

clean:
	del /q *.o main.exe
