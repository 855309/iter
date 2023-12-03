#ifndef _D_VEC_H
#define _D_VEC_H

class vec2{
public:
	double x, y;
	
	vec2();
	vec2(double _x, double _y);
	vec2(double f);
	
	vec2 operator+(vec2 const& rhs);
	vec2 operator-(vec2 const& rhs);
	vec2 operator*(vec2 const& rhs);
	vec2 operator/(vec2 const& rhs);
};

class vec3{
public:
	double x, y, z;
	vec3();
	vec3(double _x, double _y, double _z);
	vec3(double f);
	
	vec3 operator+(vec3 const& rhs);
	vec3 operator-(vec3 const& rhs);
	vec3 operator*(vec3 const& rhs);
};

#endif
