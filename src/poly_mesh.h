#ifndef POLY_MESH_H
#define POLY_MESH_H

#include "hittable.h"
#include "triangle.h"
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

#include "vec3.h"


struct poly_mesh {
	std::vector<std::vector<point3>> polygons;
	// data type for uv maps

};

void read_geometry(std::string geo_fname, poly_mesh& geometry) {
	double arr[3];
	std::string line;
	std::ifstream geofile(geo_fname);

	while(getline(geofile, line)) {
		std::stringstream ss(line);

		for(int i=0;i<3;i++) ss >> arr[i];
		point3 vertex_a(arr[0],arr[1],arr[2]);
		for(int i=0;i<3;i++) ss >> arr[i];
		point3 vertex_b(arr[0],arr[1],arr[2]);
		for(int i=0;i<3;i++) ss >> arr[i];
		point3 vertex_c(arr[0],arr[1],arr[2]);

		std::vector<point3> triangle_vertices{vertex_a,vertex_b,vertex_c};
		geometry.polygons.push_back(triangle_vertices);

	}
	geofile.close();

}


#endif
