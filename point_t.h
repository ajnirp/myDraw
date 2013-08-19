#include <GL/glut.h>

class point_t {
public:
	int x;
	int y;

	point_t(int x, int y) {
		x = x;
		y = y;
	}

	void draw() {
		glPointSize(1.0);
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}
};