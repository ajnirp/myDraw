#ifndef _FRAGMENT_T_H_
#define _FRAGMENT_T_H_

class fragment_t {
public:
	float size;
	color_t color;

	fragment_t(color_t c, float s){
		size = s;
		color = c;
	}

};

#endif