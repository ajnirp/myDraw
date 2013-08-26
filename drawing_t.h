#ifndef _DRAWING_T_H_
#define _DRAWING_T_H_

#include <list>
#include "point_t.h"
#include "line_t.h"
#include "polygon_t.h"

class drawing_t {
public:
	list<line_t> lines;
	list<polygon_t> polygons;

	drawing_t() {
	}

	void draw() {
		for (list<line_t>::iterator itr = lines.begin() ; itr != lines.end() ; itr++) itr->draw();
		for (list<polygon_t>::iterator itr = polygons.begin() ; itr != polygons.end() ; itr++) itr->draw();
	}

	void save() {

	}

	void load() {
		
	}
};

#endif