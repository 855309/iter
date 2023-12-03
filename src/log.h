#ifndef _D_LOG_H
#define _D_LOG_H

#include <iostream>
#include <string>

#include "vec.h"
#include "cx.h"

void ins_lf(int c, bool sp = true);
void clog(int v, bool sp = true);
void clog(double v, bool sp = true);
void clog(std::string v, bool sp = true);
void clog(cx v, bool sp = true);
void clog(vec2 v, bool sp = true);
void clog(vec3 v, bool sp = true);
void clnl();

#endif
