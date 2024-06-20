compile = g++ -c

all: balls_class.o quad.o circle_equation.o main_functions.o main.o
	g++ balls_class.o quad.o circle_equation.o main_functions.o main.o -o prog -lsfml-graphics -lsfml-window -lsfml-system

balls_class.o : balls_class.h balls_class.cpp
	$(compile) balls_class.cpp

quad.o : quad.h quad.cpp
	$(compile) quad.cpp

circle_equation.o : circle_equation.h circle_equation.cpp
	$(compile) circle_equation.cpp

main_functions.o : main_functions.h main_functions.cpp
	$(compile) main_functions.cpp

main.o: main.cpp
	$(compile) main.cpp

clean:
	rm *.o prog