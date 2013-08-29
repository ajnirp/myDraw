#ifndef _FILL_T_H_
#define _FILL_T_H_

#include <queue>

class fill_t {
public:
	bool checker_mode;
	color_t color_1;

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
	void draw(point_t start, color_t** array, color_t bgcolor) {
		if (not checker_mode) {
			queue<point_t*> points;
			points.push(&start);
			while(!points.empty())
			{

				point_t* present = points.front();
				points.pop();
				int x = present->x;
				int y = present->y;
				//cout<<x<<" , "<<y<<endl;

//				color_t black(0,0,0);
//				color_t b(0,0,0);
//				if(b==black) cout<<"working"<<endl;
//				else cout<<"not working"<<endl;
				//cout<<"The present cell initial color is "<< (int)array[x][y].red <<", "<<(int)array[x][y].blue<<", "<<(int)array[x][y].green<<endl;
				//cout<<"The present cell final color is "<<(int)color_1.red<<", "<<(int)color_1.blue<<", "<<(int)color_1.green<<endl;
				if(array[x][y].equals(bgcolor))
				{
					
					array[x][y]= color_1;
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
		else {
			cout<<"Checker mode ON"<<endl;
		}
	}
};

#endif