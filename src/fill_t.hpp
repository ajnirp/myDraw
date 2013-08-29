#ifndef _FILL_T_H_
#define _FILL_T_H_

#include "color_t.hpp"
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

	fill_t(color_t col_1, color_t col_2, bool ch_mode=false) {
		checker_mode = ch_mode;
		color_1 = col_1;
		color_2 = col_2;
	}

	// start = point where user clicked. The fill begins from there
	void draw(point_t start, color_t** array, int w, int h, color_t bgcolor) {
		if (not checker_mode) {
			queue<point_t*> points;
			points.push(&start);
			while(!points.empty())
			{

				point_t* present = points.front();
				points.pop();
				int x = present->x;
				int y = present->y;
				if(array[x][y].equals(bgcolor)) {
					array[x][y]= color_1;
					if (x+1 < w) {
						point_t* nextx1 = new point_t(x+1,y);
						points.push(nextx1);
					}
					if (x-1 > -1) {
						point_t* nextx0 = new point_t(x-1,y);
						points.push(nextx0);
					}
					if (y+1 < h) {
						point_t* nexty1 = new point_t(x,y+1);
						points.push(nexty1);
					}
					if (y-1 > -1) {
						point_t* nexty0 = new point_t(x,y-1);
						points.push(nexty0);
					}
				}
			}
		}
		else {
			//cout<<"Checker mode ON"<<endl;
			//bool t = true;
			queue<point_t*> points;
			points.push(&start);
			while(!points.empty())
			{

				point_t* present = points.front();
				points.pop();
				int x = present->x;
				int y = present->y;
				int a = x%32;
				int b = y%32;
				if(array[x][y].equals(bgcolor))
				{
					//if(t) {array[x][y]= color_1; t=false;}
					//else(!t) {array[x][y] = color_2;}
					if((a<16 && b<16) || (a>=16 && b>=16)) array[x][y] = color_1;
					else array[x][y] = color_2;
					point_t* nextx1 = new point_t(x+1,y);
					point_t* nextx0 = new point_t(x-1,y);
					point_t* nexty1 = new point_t(x,y+1);
					point_t* nexty0 = new point_t(x,y-1);
					points.push(nextx1);
					points.push(nextx0);
					points.push(nexty1);
					points.push(nexty0);
				}
			}
		}
	}
};

#endif