#include "func.h"
#include <cmath>
#include "log.h"

double cpx_fescape(cx cm){
	return 4;
}

cx cpx_func(cx cm, cx sd){
	return cm.square() + sd;
}

cx cpx_func_r(cx cm, cx sd, double ang){
	return cm.square() + sd * cx::from_ei(ang);
}
