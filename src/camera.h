#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

class camera {
    public:
        camera(
            point3 lookfrom,
            vec3 lookat,
			double roll,
            double vfov, // vertical field-of-view in degrees
            double aspect_ratio,
			double aperture,
			double focus_dist
        ) {
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;
			auto rollangle = degrees_to_radians(roll);
			vec3 up(0,1,0);

            w = unit_vector(-lookat);
			v = unit_vector(up - dot(up,w) * w);
			u = cross(v,w);

			//rotating the system by the roll angle:
			v = unit_vector(sin(rollangle) * u + cos(rollangle) * v);
			u = cross(v,w);

            origin = lookfrom;
            horizontal = focus_dist * (viewport_width * u);
            vertical = focus_dist * (viewport_height * v);
            lower_left_corner = origin - focus_dist * w - horizontal/2 - vertical/2;

			lens_radius = aperture/2;
        }

        ray get_ray(double s, double t) const {
			vec3 rd = lens_radius * random_in_unit_disk();
			vec3 offset = u * rd.x() + v * rd.y();
			// vec3 offset(0,0,0);
			auto apparent_origin = origin + offset;

            return ray(apparent_origin, 
			lower_left_corner + s*horizontal + t*vertical - apparent_origin);
        }

    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
		vec3 u, v, w;
		double lens_radius;
};
#endif
