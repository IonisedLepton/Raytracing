#ifndef GENERIC_OBJECT_H
#define GENERIC_OBJECT_H

#include "poly_mesh.h"
#include "hittable.h"
#include "vec3.h"
#include <vector>
#include <memory>

class generic_object: public hittable {
	public:
	generic_object() {}
	generic_object(poly_mesh geo, shared_ptr<material> m)
				: geometry(geo), mat_ptr(m) {};

	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const override;

	public:
	poly_mesh geometry;
	shared_ptr<material> mat_ptr;

};

bool generic_object::hit(const ray& r, double t_min, double t_max, hit_record&
rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;
	
	for (const auto& triangle_vertices: geometry.polygons) {
		triangle triangle_to_hit(triangle_vertices[0],
								 triangle_vertices[1],
								 triangle_vertices[2],
								 mat_ptr);
		
		if(triangle_to_hit.hit(r,t_min,closest_so_far,temp_rec)) {
			hit_anything =  true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
		return hit_anything;
	}

}

#endif
