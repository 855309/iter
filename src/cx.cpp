#include "cx.h"

#include <cmath>
#include <sstream>

cx::cx(){
	this->re = 0;
	this->im = 0;
}
	
cx::cx(double _re, double _im){
	this->re = _re;
	this->im = _im;
}
	
cx::cx(double _re){
	this->re = _re;
	this->im = 0;
}

cx cx::from_ei(double ang){
	return cx(cos(ang), sin(ang));
}
	
double cx::rad(){
	return sqrt(this->re*this->re + this->im*this->im);
}

double cx::orad(){
	return this->re*this->re + this->im*this->im;
}
	
cx cx::operator+(cx const& rhs){
	return cx(this->re + rhs.re, this->im + rhs.im);
}
	
cx cx::operator-(cx const& rhs){
	return cx(this->re - rhs.re, this->im - rhs.im);
}
	
cx cx::operator*(cx const& rhs){
	return cx(this->re*rhs.re - this->im*rhs.im, this->re*rhs.im + this->im*rhs.re);
}
	
cx cx::operator/(cx const& rhs){
	double k = rhs.re*rhs.re + rhs.im*rhs.im;
	return cx((this->re*rhs.re + this->im*rhs.im)/k, (this->re*rhs.im - this->im*rhs.re)/k);
}
	
cx cx::maxr(cx n){
	if(this->rad() > n.rad()){
		return *this;
	}
	return n;
}

cx cx::square(){
	return cx(this->re*this->re - this->im*this->im, (this->re + this->re)*this->im);
}
	
std::string cx::str(){
	std::stringstream ss;
	ss << this->re;
	
	if(this->im < 0){
		ss << " - " << -this->im;
	} 
	else{
		ss << " + " << this->im;
	}
	
	ss << "i";
	return ss.str();
}
