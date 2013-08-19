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

	canvas_t() {
		color_t black(0, 0, 0);
		canvas_t(0, 0, black);
	}

	canvas_t(int w, int h, color_t bg_c) {
		width = w;
		height = h;
		bg_color = bg_c;
	}

	void set(int w, int h, color_t bg_c, drawing_t* d) {
		width = w;
		height = h;
		bg_color = bg_c;
		drawing = d;
	}

	void clear() {

	}
};

#endif