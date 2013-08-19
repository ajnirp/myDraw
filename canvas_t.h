#ifndef _CANVAS_T_H_
#define _CANVAS_T_H_

#include "drawing_t.h"
#include "color_t.h"

class canvas_t {
public:
	drawing_t drawing;
	int width;
	int height;
	color_t bg_color;

	canvas_t();

	void clear() {

	}
};

#endif