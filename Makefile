all: main.o myDraw

myDraw:
	g++ main.o -L/usr/lib -lglut -lGLU -lGL -o myDraw

main.o:
	g++ -c -Wall main.cpp -o main.o

clean:
	rm -f *.o *.gch myDraw
