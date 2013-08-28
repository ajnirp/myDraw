#ifndef _DRAWING_T_H_
#define _DRAWING_T_H_

#include <list>
#include "point_t.h"
#include "canvas_t.h"
#include "line_t.h"
#include "polygon_t.h"

// class canvas_t;

class drawing_t {
public:
	list<line_t> lines;
	list<polygon_t> polygons;

	canvas_t* parent_canvas;

	drawing_t(canvas_t* pc) {
		parent_canvas = pc;
	}

	void draw() {
		cout << "Drawing directly\n";
		for (list<line_t>::iterator itr = lines.begin() ; itr != lines.end() ; itr++) itr->draw(parent_canvas->array, parent_canvas->width, parent_canvas->height);
		for (list<polygon_t>::iterator itr = polygons.begin() ; itr != polygons.end() ; itr++) itr->draw(parent_canvas->array, parent_canvas->width, parent_canvas->height);
	}

	void draw_array() {
		cout << "Drawing with array\n";
		for (int x = 0 ; x < parent_canvas->width ; x++) {
			for (int y = 0 ; y < parent_canvas->height ; y++) {
				color_t col = parent_canvas->array[x][y];

				float red = (float)(col.red) / 255;
				float green = (float)(col.green) / 255;
				float blue = (float)(col.blue) / 255;

				glColor3f(red, green, blue);
				glBegin(GL_POINTS);
				glVertex2f(x, y);
				glEnd();
			}
		}
	}

	void save() {

	}

	void load() {
		
	}
};

#endif