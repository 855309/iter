#include "vec.h"

#include <string>

vec2::vec2(){
	this->x = 0;
	this->y = 0;	
}
	
vec2::vec2(double _x, double _y){
	this->x = _x;
	this->y = _y;
}
	
vec2::vec2(double f){
	this->x = f;
	this->y = f;
}
	
vec2 vec2::operator+(vec2 const& rhs){
	return vec2(this->x + rhs.x, this->y + rhs.y);
}
vec2 vec2::operator-(vec2 const& rhs){
	return vec2(this->x - rhs.x, this->y - rhs.y);
}
vec2 vec2::operator*(vec2 const& rhs){
	return vec2(this->x * rhs.x, this->y * rhs.y);
}
vec2 vec2::operator/(vec2 const& rhs){
	return vec2(this->x / rhs.x, this->y / rhs.y);
}

vec3::vec3(){
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

vec3::vec3(double _x, double _y, double _z){
	this->x = _x;
	this->y = _y;
	this->z = _z;
}

vec3::vec3(double f){
	this->x = f;
	this->y = f;
	this->z = f;
}

vec3 vec3::operator+(vec3 const& rhs){
	return vec3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

vec3 vec3::operator-(vec3 const& rhs){
	return vec3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

vec3 vec3::operator*(vec3 const& rhs){
	return vec3(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z);
}
