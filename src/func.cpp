#include "func.h"
#include <cmath>
#include "log.h"

cx seed;
double vl[4] = {0, 0, 0, 0};
void cpx_init(cx sd){
	seed = sd;
}

double cpx_fescape(cx cm){
	return 4;
}

void cpx_setv(int n, double val){
	vl[n] = val;
}

cx cpx_func(cx cm){
	return cm.square() + seed * cx::from_ei(vl[0]);
}
