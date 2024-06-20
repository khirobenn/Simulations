all: bib.o main.o
	g++ bib.o main.o -o prog -lsfml-graphics -lsfml-window -lsfml-system

bib.o: bib.cpp bib.h
	g++ -c bib.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o prog