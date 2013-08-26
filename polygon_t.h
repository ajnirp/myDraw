#include <list>
#include "point_t.h"
#include "color_t.h"
#include "fill_t.h"

#ifndef _POLYGON_T_H_
#define _POLYGON_T_H_

class polygon_t {
public:
	list<point_t> vertices;

	bool filled;
	color_t border_color;
	pen_t border;
	color_t fill_color;

	polygon_t() {
	}

	polygon_t(list<point_t> vs, pen_t brdr) {
		border = brdr;
		vertices = vs;
	}

	void set_fill_color(color_t fc) {
		fill_color = fc;
	}

	void draw() {
		int num_vertices = vertices.size();
		if (num_vertices < 3) return;
		else {
			list<point_t>::iterator itr = vertices.begin();
			point_t temp(itr->x, itr->y);
			vertices.push_back(temp);
			for (int i = 0 ; i < num_vertices ; i++) {
				point_t temp1(itr->x, itr->y);
				itr++;
				point_t temp2(itr->x, itr->y);
				// cout << temp1.x << " " << temp1.y << endl;
				line_t edge(temp1, temp2, border_color);
				edge.draw();
			}
			vertices.pop_back();
		}
	}
};

#endif