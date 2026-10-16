#pragma once
#include <utilities.h>
#include <hittable.h>
#include <interval.h>

class triangle : public hittable {
public:
	triangle()
		:v0(), v1(), v2(), normal(), mat() {};

	triangle(vec3 p1, vec3 p2, vec3 p3, shared_ptr<material> m)
	: v0(p1), v1(p2), v2(p3), normal(compute_normal()), mat(m) {}

	bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
		float epsilon = std::numeric_limits<float>::epsilon();
		vec3 C1 = v1 - v0;
		vec3 C2 = v2 - v0;
		vec3 C3 = r.origin() - v0;
		vec3 R1 = cross(r.direction(), C2);
		vec3 R2 = cross(C3, C1);
		float Cs = dot(C1, R1);
		if (-epsilon < Cs && Cs < epsilon) return false;
		float t = (dot(C2,R2))/Cs;
		float u = (dot(C3,R1))/Cs;
		float v = (dot(r.direction(),R2))/Cs;
		if (u < 0 || v < 0 || u + v > 1) return false;
		if (t <= ray_t.min) return false;
		if (t < ray_t.max) {
			rec.t = t;
			rec.p = r.at(t);
			rec.set_face_normal(r, normal);
			rec.mat = mat.get();
			return true;
		}
		return false;
	}
private:
	vec3 compute_normal() const{
		const vec3 edge1 = v1 - v0;
		const vec3 edge2 = v2 - v0;
		vec3 n = cross(edge1, edge2);
		const float normalize = sqrt(pow(n.x, 2) + pow(n.y, 2) + pow(n.z, 2));
		n /= normalize;
		return n;
	}

	vec3 v0;
	vec3 v1;
	vec3 v2;
	vec3 normal;
	shared_ptr<material> mat;
};