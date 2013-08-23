#include <cmath>
#include <iostream>
#include <cstdlib>
#include "required.h"
#include <GLUT/glut.h>

using namespace std;

int win_width = 1024;
int win_height = 768;

canvas_t canvas;
bool canvas_exists = false;

void reshape(int w, int h);

void make_new_canvas() {
	if (!canvas_exists) {
		cout << "Making a new canvas. Enter details:\n";
		int w; cout << "\tCanvas width: "; cin >> w;
		int h; cout << "\tCanvas height: "; cin >> h;

		cout << "Enter RGB for background color (0-255):\n";
		int r; cout << "\tR: "; cin >> r;
		int g; cout << "\tG: "; cin >> g;
		int b; cout << "\tB: "; cin >> b;
		color_t bg_c(r, g, b);
		canvas.set(w, h, bg_c, NULL);
		canvas_exists = true;
		//reshape(w,h);
		glutReshapeWindow(w,h);
		glutPostRedisplay();

		cout << "Initialized new canvas\n";
	}
	else {
		cerr << "A canvas already exists!\n";
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	// color_t c(255, 255, 255);
	// line_t l(500, 200, 600, 100, c);
	// l.draw();

	//cout<<glGetString(GL_VERSION)<<endl;
	
	point_t p0(100, 100);
	point_t p1(200, 200);
	point_t p2(300, 150);

	list<point_t> points;
	points.push_back(p0);
	points.push_back(p1);
	points.push_back(p2);

	color_t white(255, 255, 255);
	polygon_t poly(points, white);
	poly.draw();

	if (canvas_exists) {
	}

	glFlush();
}


void reshape(int w, int h) {
	if (h == 0) h = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho( 0.0, (GLdouble)w, 0.0, (GLdouble)h, -1., 1. );
	glViewport( 0, 0, w, h );

	win_width = w;
	win_height = h;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 'n': {
			make_new_canvas();
		}
		break;
		case 'd': {
			if (!canvas_exists) {
				cerr << "No canvas to draw on! Make a new canvas by pressing 'n'.\n";
			}
			else {

			}
		}
		break;
		// case 's':
		// case 'l':
	}
}

void mouse(int button, int state, int x, int y) {}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(win_width, win_height);

	glutCreateWindow("myDraw");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);



	glutMainLoop();
	return 0;
}