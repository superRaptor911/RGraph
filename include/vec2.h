/**
 * @file vec2.h
 * @author Raptor (Aditya Aravind) (raptor.inc2018@gmail.com)
 * @brief 
 * @version 0.1
 * @date 11-06-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef VEC2_H
#define VEC2_H


#include <cmath>

namespace rg
{
	class vec2
	{

	public:

		float x , y;
	
		vec2() { x = 0.f; y = 0.f;}
		vec2(float i , float j) { x = i; y = j;}

		/**
		 * @brief Get magnitude of the vector.
		 * 
		 * @return float 
		 */
		float length() const { return std::sqrt(x*x + y*y);}
		
		/**
		 * @brief Get square of magnitude of the vector.
		 * 
		 * @return float 
		 */
		float length2() const { return (x*x + y*y);}

		/**
		 * @brief Convert vector to unit vector.
		 * 
		 */
		void normalize();
		
		/**
		 * @brief Get unit vector.
		 * 
		 * @return vec2
		 */
		vec2 normalized() const;

		/**
		 * @brief Get the angle (in radians).
		 * 
		 * @return float 
		 */
		float angle() const { return std::atan2(y,x);}

		/**
		 * @brief Get angle between 2 vectors (in radians).
		 * 
		 * @param v 
		 * @return float 
		 */
		float angleBetween(const vec2 &v) const; 

		/**
		 * @brief Rotate vector by given angle.
		 * 
		 * @param angle 
		 */
		void rotate(float angle);

		

		vec2 operator + (const vec2 &V2) { return vec2(x + V2.x, y + V2.y);}

		vec2 operator - (const vec2 &V2) { return vec2(x - V2.x, y - V2.y);}

		vec2 operator * (const vec2 &V2) { return vec2(x * V2.x, y * V2.y);}

		vec2 operator * (const float scalar) { return vec2(x * scalar, y * scalar);}

		vec2 operator / (const vec2 &V2) { return vec2(x / V2.x, y / V2.y);}

		vec2 operator / (const float scalar) { return vec2(x / scalar, y / scalar);}

		void operator += (const vec2 &V2) { x += V2.x; y += V2.y;}

		void operator -= (const vec2 &V2) { x -= V2.x; y -= V2.y;}

		void operator *= (const vec2 &V2) { x *= V2.x; y *= V2.y;}

		void operator *= (const float scalar) { x += scalar; y += scalar;}

		void operator /= (const vec2 &V2) { x /= V2.x; y /= V2.y;}

		void operator /= (const float scalar) { x /= scalar; y /= scalar;}

	};
	
	
}

#endif
