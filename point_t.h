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

	void draw(pen_t pen, color_t** arr, int arr_w, int arr_h) {
		// glPointSize(pen.size);

		float red = (float)(pen.color.red) / 255;
		float green = (float)(pen.color.green) / 255;
		float blue = (float)(pen.color.blue) / 255;

		glColor3f(red, green, blue);
		glBegin(GL_POINTS);
		for (int xx = 0 ; xx < pen.size ; xx++) {
			for (int yy = 0 ; yy < pen.size ; yy++) {
				if (x+xx < arr_w and y+yy < arr_h and x+xx > -1 and y+yy > -1) {
					glVertex2f(x+xx, y+yy);
					arr[x+xx][y+yy] = pen.color;
				}
			}
		}
		glEnd();

	}
};

#endif