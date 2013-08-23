#include <cmath>
#include <iostream>
#include <cstdlib>
#include "required.h"
#include <GL/glut.h>

using namespace std;

/* Global vars */
int win_width = 1024;
int win_height = 768;

canvas_t* canvas = NULL;
bool canvas_exists = false;

/* Function declarations */
void make_new_canvas();
void display(void);
void reshape(int, int);
void keyboard(unsigned char, int, int);
void mouse(int, int, int, int);

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

		canvas = new canvas_t(w, h, bg_c, NULL);

		// canvas.set(w, h, bg_c, NULL);
		canvas_exists = true;

		// resize the window
		glutReshapeWindow(w, h);
		glutPostRedisplay();

		glClearColor(r/255.0, g/255.0, b/255.0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		cout << "Initialized new canvas\n";
	}
	else {
		cerr << "A canvas already exists!\n";
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	/* Test code here */

	// cout << glGetString(GL_VERSION) << endl;

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