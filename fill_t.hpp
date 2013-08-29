#ifndef _FILL_T_H_
#define _FILL_T_H_

#include <queue>

class fill_t {
public:
	bool checker_mode;
	color_t color_1;
	color_t color_2;

	fill_t() {
		color_t black(0, 0, 0);
		color_1 = black;
		checker_mode = false;
	}

	fill_t(color_t col_1, bool ch_mode=false) {
		checker_mode = ch_mode;
		color_1 = col_1;
	}

	// start = point where user clicked. The fill begins from there
	void draw(point_t start, color_t** arr) {
		if (not checker_mode) {

		}
		else {
		}
	}
};

#endif