#ifndef _PEN_T_H_
#define _PEN_T_H_

#include "color_t.hpp"

class pen_t {
public:
	float size; // thickness of the pen line
	color_t color;

	bool eraser;

	pen_t() {
		color_t black(0, 0, 0);
		pen_t(black, 3.0, false);
	}

	pen_t(color_t c, float s = 2.0, bool er = false) {
		color = c;
		size = s;
		eraser = er;
	}
};

#endif