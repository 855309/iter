#include "iter.h"

#include "func.h"
#include "color.h"
#include "log.h"

iterator::iterator(int itr, int _type, int _mode, cx _seed, double _ang){
	this->iterations = itr;
	this->type = _type;
	this->mode = _mode;
	this->seed = _seed;
	this->ang = _ang;
}

void iterator::set_itrn(int n){
	this->iterations = n;
}

int iterator::iterate(cx cm, int num){
	cx res = cm;
	double esc_ords = cpx_fescape(cm);

	cx sd = this->seed;
	
	// mdb
	if(type == 0){
		sd = cm;
	}
	
	if(cm.orad() > esc_ords) return 0;
	for(int i = 1; i <= num; i++){
		// zoom
		if(this->mode == 0){
			res = cpx_func(res, sd);
		}
		
		// apply_ei (rot)
		if(this->mode == 1){
			res = cpx_func_r(res, sd, this->ang);
		}
		
		if(res.orad() > esc_ords){
			return i + 1 - log(log(res.orad()))/log(2);
			// return i;
		}
	}
	
	return -1;
}

void iterator::fillpix(vec2 pos, int et){
	vec3 gcl = colfunc(et, iterations);
	rgb_t pxcl = make_colour(gcl.x, gcl.y, gcl.z);
	this->c_img.set_pixel(pos.x, pos.y, pxcl);
}

void iterator::paint(vec2 sx, vec2 sy, int w, int h){
	this->c_img = bitmap_image(w, h);
	
	/*ins_lf(0);
	clog("Started iteration:");
	clog(iterations);
	clog("iterations.");
	clnl();*/
	
	double sc_fx = (sx.y - sx.x)/((double)w);
	double sc_fy = (sy.y - sy.x)/((double)h);
	for(int x = 0; x < w; x++){
		double xv = sx.x + x*sc_fx;
		for(int y = 0; y < h; y++){
			double yv = sy.y - y*sc_fy;
			cx cm(xv, yv);
			int et = this->iterate(cm, iterations);
			this->fillpix(vec2(x, y), et);
		}
	}
}

bitmap_image iterator::getimg(){
	return this->c_img;
}

