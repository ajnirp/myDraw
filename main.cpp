#include <cmath>
#include <iostream>
#include <cstdlib>
#include "required.h"
#include <GL/glut.h>

using namespace std;

int win_width = 1024;
int win_height = 768;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	// color_t c(255, 255, 255);
	// line_t l(500, 200, 600, 100, c);
	// l.draw();
	glutSwapBuffers();
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
		case 'n':
			cout << "Canvas width: ";
			cin >> win_width;
			cout << "Canvas height: ";
			cin >> win_height;
			cout << "Enter RGB for background color (0-255)\n";
			unsigned char r, g, b;
			cout << "R: "; cin >> r;
			cout << "G: "; cin >> g;
			cout << "B: "; cin >> b;
		// case 100: // d
		// case 115: // s
		// case 108: // l
	}
}

void mouse(int button, int state, int x, int y) {}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(win_width, win_height);

	glutCreateWindow("myDraw");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	glutMainLoop();
	return 0;
}