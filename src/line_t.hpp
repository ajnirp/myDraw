#ifndef _LINE_T_H_
#define _LINE_T_H_

#include <cmath>
#include "point_t.hpp"
#include "pen_t.hpp"
#include "color_t.hpp"

class line_t {
private:
	void swap (int &x, int &y) {
	  int temp = x;
	  x = y; y = temp;
	}
public:
	point_t v0;
	point_t v1;

	pen_t pen;

	line_t() {
	}

	line_t(int x0, int y0, int x1, 	int y1, pen_t p) {
		v0.x = x0;
		v0.y = y0;
		v1.x = x1;
		v1.y = y1;
		pen = p;
	}

	line_t(point_t p0, point_t p1, pen_t p) {
		v0 = p0;
		v1 = p1;
		pen = p;
	}

	void set_points(point_t p0, point_t p1) {
		v0 = p0;
		v1 = p1;
	}

	void set_xy(int x0, int y0, int x1, int y1) {
		v0.x = x0;
		v0.y = y0;
		v1.x = x1;
		v1.y = y1;
	}

	void set_pen(pen_t p) {
		pen = p;
	}

	// For the following function we modified the implementation
	// of Bresenham's line drawing algorithm that was given
	// as a demonstration
	
	void draw(color_t** arr, int arr_w, int arr_h) {
		int x0 = v0.x;
		int y0 = v0.y;
		int x1 = v1.x;
		int y1 = v1.y;

		bool steep = abs(y1 - y0) > abs(x1 - x0);
		if (steep) {
			swap(x0, y0);
			swap(x1, y1);
		}
		if (x0 > x1) {
			swap(x0, x1);
			swap(y0, y1);
		}
		int deltax = x1 - x0;
		int deltay = abs(y1 - y0);

		int error = 0;

		int ystep;
		int y = y0;

		if (y0 < y1) ystep = 1; else ystep = -1;

		for (int x=x0; x <= x1; x++) {
			if (steep) {
				point_t p(y, x);
				p.draw(pen, arr, arr_w, arr_h);
			}
			else {
				point_t p(x, y);
				p.draw(pen, arr, arr_w, arr_h);
			}

			error = error + deltay;
			if ( (error << 1) >= deltax) {
			  y = y + ystep;
			  error = error - deltax;
			}
		}
	}
};

#endif