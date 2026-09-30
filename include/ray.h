#include <include\vec3.h>

class ray {
public:
	ray() : origin(), direction() {}
	ray(vec3& point, vec3& dir) : origin(point), direction(dir) {}
private:
	vec3 origin;
	vec3 direction;
};