#ifndef _COLOR_T_H_
#define _COLOR_T_H_

#include <iostream>
using namespace std;


class color_t {
public:
	unsigned char red;
	unsigned char blue;
	unsigned char green;

	// int red;
	// int green;
	// int blue;

	color_t() {
		color_t(0, 0, 0);
	}

	color_t(unsigned char r, unsigned char g, unsigned char b) {
		red = r;
		green = g;
		blue = b;
	}

	bool operator==(color_t& b)
	{
		if(red==b.red && blue==b.blue && green==b.green) return true;
		return false;
	}

	bool equals(color_t b)
	{
		int r1 = red;
		int b1 = blue;
		int g1 = green;
		int r2 = b.red;
		int b2 = b.blue;
		int g2 = b.green;
		if(r1==r2 && b1==b2 && g1==g2)
		{
			//cout<<"Found"<<endl;
			return true;
		}
		else return false;
	}

	// color_t(int r, int g, int b) {
	// 	red = r;
	// 	green = g;
	// 	blue = b;
	// }
};

#endif