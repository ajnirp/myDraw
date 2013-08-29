all: myDraw

myDraw: main.o
#	g++ main.o -L/usr/lib -lglut -lGLU -lGL -o myDraw
	g++ main.o -framework opengl -framework glut -o myDraw

main.o: main.cpp drawing_t.h line_t.h point_t.h canvas_t.h pen_t.h required.h polygon_t.h color_t.h fill_t.h
	g++ -c -Wall main.cpp -o main.o

clean:
	rm -f *.o *.gch myDraw
