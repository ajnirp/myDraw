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

	void draw(pen_t** arr) {
		cout << "Drawing directly\n";
		for (list<line_t>::iterator itr = lines.begin() ; itr != lines.end() ; itr++) itr->draw(arr);
		for (list<polygon_t>::iterator itr = polygons.begin() ; itr != polygons.end() ; itr++) itr->draw(arr);
	}

	void draw_array(pen_t** arr) {
		cout << "Drawing with array\n";
		for (int x = 0 ; x < parent_canvas->width ; x++) {
			for (int y = 0 ; y < parent_canvas->height ; y++) {
				pen_t pen;
				pen = arr[x][y];

				glPointSize(pen.size);

				float red = (float)(pen.color.red) / 255;
				float green = (float)(pen.color.green) / 255;
				float blue = (float)(pen.color.blue) / 255;

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