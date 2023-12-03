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

double zoom_f = 1.05;
double start_w;
int width, height;
cx sd;
int iters;
int threads;

vec2 sx, sy;

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

void itr_nsave(int c_sc, int kl){
	iterator itr(iters);
	itr.paint(sx, sy, width, height);
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

int main(int argc, char** argv){
	if(argc == 10){
		loadmap(argv[1]);
		start_w = std::stoi(argv[2]);
		
		sd = cx(std::stod(argv[3]), std::stod(argv[4]));
		
		iters = std::stoi(argv[5]);
		
		width = std::stoi(argv[6]);
		height = std::stoi(argv[7]);
		out_path = argv[8];
		threads = std::stoi(argv[9]);
	}
	else{
		std::cout << "Usage:" << std::endl;
		std::cout << argv[0] << " [colormap_file] [start_w] [c.re] [c.im] [iterations] [img_w] [img_h] [out_path] [threads]" << std::endl;
		return -1;
	}
	
	/*for(int i = 0; i < threads; i++){
		thread_stat.push_back(false);
	}*/
	
	thr_running = 0;
	
	sx = vec2(-start_w, start_w);
	sy = (sx / width) * height;
	
	cpx_init(sd);

	double s_scl = 1;
	
	double f = 0;
	double maxf = 2 * M_PI;
	double stepc = 1200;
	double step = (maxf - f)/stepc;
	int kl = floor(log10(stepc)) + 1;
	
	for(int i = 0; i < stepc; i++){
		double c_f = i * step;
		cpx_setv(0, c_f);
		int c_sc = i + 1;
		
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
		
		std::thread c_t(itr_nsave, c_sc, kl);
		c_t.detach();
	}
/*
					vec2 cnt((sx.y + sx.x)/2, (sy.y + sy.x)/2);
					sx = (sx - cnt.x)/zoom_f + cnt.x;
					sy = (sy - cnt.y)/zoom_f + cnt.y;
					
					s_scl *= zoom_f;
*/
	
	return 0;
}
