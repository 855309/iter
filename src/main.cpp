#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <thread>
#include <atomic>

#include "log.h"
#include "vec.h"
#include "func.h"
#include "color.h"
#include "iter.h"

double start_w;
int width, height;
cx sd;
int iters;
int threads;

std::atomic_int thr_running;
std::string out_path;

// path join
std::string join_path(std::string p1, std::string p2)
{
    char sep = '/';
    std::string tmp = p1;

#ifdef _WIN32
    sep = '\\';
#endif

    if(p1[p1.length() - 1] != sep){
        tmp += sep;
        return tmp + p2;
    }
    else{
        return p1 + p2;
    }
}
// end

int type = 0;
int mode = 0;
void itr_nsave(int c_sc, int kl, vec2 sx_t, vec2 sy_t, double ang){
	iterator itr(iters, type, mode, sd, ang);
	itr.paint(sx_t, sy_t, width, height);
	bitmap_image img = itr.getimg();
	
	std::stringstream sstr;
	sstr << "img";
	int c_sck = floor(log10(c_sc)) + 1;
	for(int j = 0; j < kl - c_sck; j++){
		sstr << "0";
	}
	sstr << c_sc << ".bmp";
	img.save_image(join_path(out_path, sstr.str()));
	
	thr_running--;
}

vec2 sx, sy;

int stepc = 0;
double fac_start, fac_end;
vec2 ctr;
int main(int argc, char** argv){
	if(argc == 17){
		loadmap(argv[1]);
		start_w = std::stoi(argv[2]);
		
		ctr = vec2(std::stod(argv[3]), std::stod(argv[4]));
		
		std::string typ_s(argv[5]);
		if(typ_s == "mdb"){
			type = 0;
		}
		else if(typ_s == "jul"){
			type = 1;
		}
		else{
			ins_lf(1);
			clog("Unknown func type.");
			clnl();
			return -1;
		}
		
		sd = cx(std::stod(argv[6]), std::stod(argv[7]));
		
		iters = std::stoi(argv[8]);
		
		width = std::stoi(argv[9]);
		height = std::stoi(argv[10]);
		out_path = argv[11];
		threads = std::stoi(argv[12]);
		
		std::string m_st(argv[13]);
		if(m_st == "zoom"){
			mode = 0;
		}
		else if(m_st == "apply_ei"){
			mode = 1;
		}
		else{
			ins_lf(1);
			clog("Unknown mode.");
			clnl();
			return -1;
		}
		
		fac_start = std::stod(argv[14]);
		fac_end = std::stod(argv[15]);
		stepc = std::stoi(argv[16]);
	}
	else{
		std::cout << "Usage:" << std::endl;
		std::cout << argv[0] << " [colormap_file] [start_w] [s.re] [s.im] [mdb / jul] [c.re] [c.im] [iterations] [img_w] [img_h] [out_path] [threads] [zoom / apply_ei] [fac_start] [fac_end] [steps (frames)]" << std::endl;
		return -1;
	}
	
	/*for(int i = 0; i < threads; i++){
		thread_stat.push_back(false);
	}*/
	
	thr_running = 0;
	
	sx = vec2(-start_w, start_w);
	sy = ((sx / width) * height) + ctr.y;
	sx = sx + ctr.x;
	
	if(mode == 0){
		sx = sx * fac_start;
		sy = sy * fac_start;
	}
	else if(mode == 1){
		fac_start *= M_PI;
		fac_end *= M_PI;
	}
	
	// rot.
	double step = (fac_end - fac_start) / stepc;
	
	
	int kl = floor(log10(stepc)) + 1;
	double c_f = 0;
	
	for(int i = 0; i < stepc; i++){
		int c_sc = i + 1;
		if(mode == 1){
			c_f = fac_start + i * step;
		}
		
		bool d_tf = false;
		while(!d_tf){
			d_tf = (thr_running < threads);
		}
		
		ins_lf(0);
		clog("Iterations:");
		clog(iters, false);
		clog(", Step:");
		clog(c_sc, false);
		clog("/", false);
		clog(stepc, false);
		clog(".");
		clnl();
		
		thr_running++;
		
		std::thread c_t(itr_nsave, c_sc, kl, sx, sy, c_f);
		c_t.detach();
		
		if(mode == 0){
			vec2 cnt((sx.y + sx.x)/2, (sy.y + sy.x)/2);
			sx = (sx - cnt.x)/fac_end + cnt.x;
			sy = (sy - cnt.y)/fac_end + cnt.y;
		}
	}
	
	while(thr_running != 0){
		// wait
	}
	
	ins_lf(0);
	clog("Complete.");
	clnl();
	
	return 0;
}
