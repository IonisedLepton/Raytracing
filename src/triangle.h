#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "vec3.h"

class triangle: public hittable {
	public:
		triangle(){}
		triangle(point3 vertex_a,
				 point3 vertex_b,
				 point3 vertex_c,
				 shared_ptr<material> m):
					a(vertex_a),
				    b(vertex_b),
					c(vertex_c),
					mat_ptr(m) {};
	
	virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

	public:
		point3 a,b,c;
		shared_ptr<material> mat_ptr;
};

bool triangle::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
	// The algorithm is based on the Moller-Trumbore intersection algorithm
	// http://www.graphics.cornell.edu/pubs/1997/MT97.pdf
	vec3 u = b - a;
	vec3 v = c - a;
	vec3 w = cross(u,v);
	vec3 p = r.origin();
	vec3 q = r.direction();
	const double EPSILON = 0.0000001;

	vec3 h = cross(q,v);
	auto det = dot(h,u);
	if (det > -EPSILON && det < EPSILON)
		return false; // ray parallel to triangle

	vec3 l = p - a;
	vec3 k = cross(l,u);

	// ray = p + tq ; triangle = a + alpha*u + beta*v
	auto alpha = dot(h,l)/det;
	if (alpha < 0 || alpha > 1) 
		return false;
	auto beta  = dot(k,q)/det;
	if (beta < 0 || alpha + beta > 1)
		return false;
	auto t     = dot(k,v)/det;
	if (t < t_min || t > t_max)
		return false;

	rec.t = t;
	rec.p = r.at(rec.t);
	vec3 outward_normal = unit_vector(w);
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;
	return true;
}

#endif
