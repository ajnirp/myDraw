#ifndef _POINT_T_H_
#define _POINT_T_H_

#include "pen_t.h"
#include "color_t.h"
#include <GL/glut.h>

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

	void set(int xx, int yy) {
		x = xx;
		y = yy;
	}

	void draw(pen_t pen, pen_t** arr) {
		glPointSize(pen.size);

		float red = (float)(pen.color.red) / 255;
		float green = (float)(pen.color.green) / 255;
		float blue = (float)(pen.color.blue) / 255;

		glColor3f(red, green, blue);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();

		arr[x][y] = pen;
	}
};

#endif