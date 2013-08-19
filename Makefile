all: myDraw

myDraw: main.o
	g++ -std=c++11 main.o -L/usr/lib -lglut -lGLU -lGL -o myDraw

main.o:
	g++ -std=c++11 -c -Wall main.cpp -o main.o

clean:
	rm -f *.o *.gch myDraw
