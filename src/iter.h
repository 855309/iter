#ifndef _D_ITER_H
#define _D_ITER_H

#include <vector>
#include "vec.h"
#include "cx.h"

#include "../lib/bitmap_image.hpp"

class iterator{
private:
	bitmap_image c_img;
	int iterations;
	int type, mode;
	double ang;
	cx seed;
	
	void fillpix(vec2 pos, int et);
	int iterate(cx cm, int num);
public:
	iterator(int itr, int _type, int _mode, cx _seed, double _ang);
	
	void paint(vec2 sx, vec2 sy, int w, int h);
	bitmap_image getimg();
	void iter_init();
	void set_itrn(int n);
};

#endif
