#ifndef _CANVAS_T_H_
#define _CANVAS_T_H_

#include "drawing_t.h"
#include "color_t.h"

class canvas_t {
public:
	drawing_t* drawing;
	int width;
	int height;
	color_t bg_color;

	pen_t** array;

	canvas_t(int w, int h, color_t bg_c, drawing_t* d) {
		width = w;
		height = h;

		// Allocate memory for the array and clear it
		array = new pen_t*[width];
		for (int i = 0 ; i < width ; i++) array[i] = new pen_t[height];
		clear();

		bg_color = bg_c;
		drawing = d;
	}

	void clear() {
		for (int x = 0 ; x < width ; x++) {
			for (int y = 0 ; y < height ; y++) {
				array[x][y].color = bg_color;
			}
		}
	}
};

#endif