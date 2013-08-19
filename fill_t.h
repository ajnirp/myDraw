#ifndef _FILL_T_H_
#define _FILL_T_H_

enum fill_mode {
	solid = 0,
	checkerboard = 1
};

class fill_t {
	fill_mode mode;
	color_t color_1;
	color_t color_2;

	void draw() {
		
	}
};

#endif