#include "color_t.h"

enum pen_mode {
	pen = 0, //draw with the current pen color
	eraser = 1 // draw with the color of the background
};

class pen_t {
private:
	int size; // thickness of the pen line
	color_t color;

public:
	pen_mode mode;
	pen_t(int s, pen_mode p_mode = pen) {
		size = s;
		mode = p_mode;
	}
};