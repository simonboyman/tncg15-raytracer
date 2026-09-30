#pragma once
#include <vec3.h>

class triangle {
public: 
	vec3 compute_normal(const vec3& v0, const vec3& v1, const vec3& v2) {} // ska funktionen vara const eller &?
private:
	vec3 v0;
	vec3 v1;
	vec3 v2;
	vec3 normal;
	vec3 color;
};