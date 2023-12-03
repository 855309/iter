#include "color.h"

#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include "log.h"

/* str parsing */
vec3 parsergb(std::string colstr)
{
    std::string t = colstr + " ";

    std::stringstream stream;
    std::vector<int> ivec;

    for(char c : t){
        if(c == ' '){
            ivec.push_back(std::stoi(stream.str()));
            stream.str("");
        }
        else{
            stream << c;
        }
    }
    
    return vec3(ivec[0], ivec[1], ivec[2]);
}
/* end str parsing */

int pathln = 0;
double pdiff;
std::vector<vec3> path;

void loadmap(std::string fpath){
	std::ifstream rsm(fpath);
	std::string rln;
	while(getline(rsm, rln)){
		path.push_back(parsergb(rln));
		pathln++;
	}
	pdiff = (double)1/(double)(pathln - 1);
}

vec3 cmap(double x){
	int p = floor(x / pdiff);
	if(p == pathln - 1){
		return path[pathln - 1];
	}
	vec3 c1 = path[p];
	vec3 c2 = path[p + 1];

	double s = (x / pdiff) - p;
	return (c1 + (c2 - c1) * s);
}

vec3 colfunc(double t, double maxt){
	// y: (1/2) * (1 + smoothsq((3*M_PI/maxt) * (t - M_PI/4)))
	// z: (1/2) * (1 - smoothsq(M_PI/2 - (3*M_PI/maxt) * (t - M_PI/4)))
	//return vec3((double)t/(double)maxt, 0.5 * (1 + smoothsq((2*M_PI/(fr_ml*maxt)) * (t - M_PI/4), dlt)), 0.5 * (1 - smoothsq(M_PI/2 - (2*M_PI/(fr_ml*maxt)) * (t - M_PI/4), dlt)));
	if(t == -1){
		return vec3(0,0,0);
	}
	
	vec3 l = cmap(t/maxt);
	return l;
}
