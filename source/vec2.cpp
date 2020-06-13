/**
 * @file vec2.cpp
 * @author Raptor (Aditya Aravind) (raptor.inc2018@gmail.com)
 * @brief 
 * @version 0.1
 * @date 11-06-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <vec2.h>

using namespace rg;


void vec2::normalize()
{
	float l = std::sqrt(x*x + y*y);
	x /= l;  y /= l;
}


vec2 vec2::normalized() const
{
	vec2 rtn_val; float l = std::sqrt(x*x + y*y);
	rtn_val.x /= l;  rtn_val.y /= l;
	return rtn_val;
}


float vec2::angleBetween(const vec2 &v) const
{
	return 0.f;

}


