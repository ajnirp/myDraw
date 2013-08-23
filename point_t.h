#ifndef _POINT_T_H_
#define _POINT_T_H_

#include "color_t.h"
#include <GLUT/glut.h>

#include <iostream>
using namespace std;

class point_t {
public:
	int x;
	int y;

	point_t() {
		x = 0;
		y = 0;
	}

	point_t(int xx, int yy) {
		x = xx;
		y = yy;
	}

	void draw(color_t color) {
		glPointSize(1.0);

		float red = (float)(color.red) / 255;
		float green = (float)(color.green) / 255;
		float blue = (float)(color.blue) / 255;

		glColor3f(red, green, blue);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}
};

#endif