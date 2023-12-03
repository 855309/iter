#include "log.h"

std::string cds[] = {"INF", "ERR"};
void ins_lf(int c, bool sp){
	std::cout << "[" << cds[c] << "]";
	if(sp){
		std::cout << " ";
	}
}

void clog(int v, bool sp){
	std::cout << v;
	if(sp){
		std::cout << " ";
	}
}

void clog(double v, bool sp){
	std::cout << v;
	if(sp){
		std::cout << " ";
	}
}

void clog(std::string v, bool sp){
	std::cout << v;
	if(sp){
		std::cout << " ";
	}
}

void clog(cx v, bool sp){
	std::cout << v.str();
	if(sp){
		std::cout << " ";
	}
}

void clog(vec2 v, bool sp){
	std::cout << "(" << v.x << ", " << v.y << ")";
	if(sp){
		std::cout << " ";
	}
}

void clog(vec3 v, bool sp){
	std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	if(sp){
		std::cout << " ";
	}
}

void clnl(){
	std::cout << std::endl;
}
