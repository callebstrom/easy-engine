#pragma once
#include <Eigen\Core>
#include <vector>

#ifndef BASE_DATA_TYPES
typedef unsigned char byte;
typedef struct obj_vector {
	std::vector<Eigen::Vector3d> vertices;
	std::vector<Eigen::Vector2d> uvs;
	std::vector<Eigen::Vector3d> normals;
};
#endif // !BASE_DATA_TYPES