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
}