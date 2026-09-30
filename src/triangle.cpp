#include <include/triangle.h>
#include <cmath>

vec3 compute_normal(const vec3& v0, const vec3& v1, const vec3& v2) {
	vec3 edge1 = v1 - v0;
	vec3 edge2 = v2 - v0;
	vec3 normal = cross(edge1, edge2);
	double normalize = sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2));
	normal /= normalize;
	return normal;
}