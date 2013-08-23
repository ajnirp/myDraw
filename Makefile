all: myDraw

myDraw: main.o
	g++ main.o -o myDraw -framework opengl -framework glut

main.o: main.cpp drawing_t.h polygon_t.h fill_t.h point_t.h line_t.h pen_t.h canvas_t.h required.h color_t.h
	g++ -c -Wall main.cpp -o main.o

clean:
	rm -f *.o *.gch myDraw
