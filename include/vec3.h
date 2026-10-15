#pragma once
#include "utilities.h"
class vec3 {
public:
	vec3() : x(0.0), y(0.0), z(0.0) {}
	vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {} // constructor
	// ska det vara const nånstans/&reference??

	vec3 operator-() const { return {-x, -y, -z}; }

	vec3& operator+=(const vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3& operator-=(const vec3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	vec3& operator*=(float t) {
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	vec3& operator/=(float t) {
		x /= t;
		y /= t;
		z /= t;
		return *this;
	}

	float length() const {
		return std::sqrt(length_squared());
	}

	double length_squared() const {
		return x*x + y*y + z*z;
	}

	float x;
	float y;
	float z;

	static vec3 random() {
		return vec3(random_float(), random_float(), random_float());
	}

	static vec3 random(float min, float max) {
		return vec3(random_float(min,max), random_float(min,max), random_float(min,max));
	}
};

inline vec3 operator*(float t, const vec3& v) {
	return {t*v.x, t*v.y, t*v.z};
}

inline vec3 operator*(const vec3& a, const vec3& b) {
	return {a.x * b.x, a.y * b.y, a.z * b.z};
}

inline vec3 operator/(const vec3& v, float t) {
	return (1/t) * v;
}

inline vec3 operator-(const vec3& v1, const vec3& v2) {
	return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline vec3 operator+(const vec3& v1, const vec3& v2) {
	return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

inline vec3 cross(const vec3& v1, const vec3& v2) {
	return {v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
}

inline float dot(const vec3& v1, const vec3& v2) {
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}


inline vec3 unit_vector(const vec3& v) {
	return v / v.length();
}

inline vec3 random_unit_vector() {
	while (true) {
		auto p = vec3::random(-1,1);
		auto lensq = p.length_squared();
		if (1e-160 < lensq && lensq <= 1)
			return p / sqrt(lensq);
	}
}

inline vec3 random_on_hemisphere(const vec3& normal) {
	vec3 on_unit_sphere = random_unit_vector();
	if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return on_unit_sphere;
	else
		return -on_unit_sphere;
}