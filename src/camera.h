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
            double aspect_ratio
        ) {
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;
			auto rollangle = degrees_to_radians(roll);
			vec3 up(0,1,0);

            auto w = unit_vector(-lookat);
			auto v = unit_vector(up - dot(up,w) * w);
			auto u = cross(v,w);
			//rotating the system by the roll angle:
			v = unit_vector(sin(rollangle) * u + cos(rollangle) * v);
			u = cross(v,w);

            origin = lookfrom;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            lower_left_corner = origin - w - horizontal/2 - vertical/2;
        }

        ray get_ray(double s, double t) const {
            return ray(origin, lower_left_corner + s*horizontal + t*vertical - origin);
        }

    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
};
#endif
