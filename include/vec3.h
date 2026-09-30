class vec3 {
public:
	vec3() : x(0.0), y(0.0), z(0.0) {}
	vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {} // constructor
	// ska det vara const nånstans/&reference??

	vec3& operator+=(const vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}

	vec3& operator-=(const vec3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	vec3& operator*=(double t) {
		x *= t;
		y *= t;
		z *= t;
	}

	vec3& operator/=(double t) {
		x /= t;
		y /= t;
		z /= t;
	}

	double x;
	double y;
	double z;
};

vec3 operator-(const vec3& v1, const vec3& v2) {
	return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

vec3 cross(const vec3& v1, const vec3& v2) {
	return vec3(v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x); // behövs inte operator* ??
}