#ifndef _COLOR_T_H_
#define _COLOR_T_H_

class color_t {
public:
	unsigned char red;
	unsigned char blue;
	unsigned char green;

	color_t() {
		color_t(0, 0, 0);
	}

	color_t(unsigned char r, unsigned char g, unsigned char b) {
		red = r;
		green = g;
		blue = b;
	}
};

#endif