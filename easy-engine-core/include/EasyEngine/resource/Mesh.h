#ifndef RENDERABLE_3D_H
#define RENDERABLE_3D_H
#pragma once

#include <Eigen/Core>
#include <boost/scoped_ptr.hpp>

#include <EasyEngine/resource/Renderable.h>
#include <EasyEngine/resource/Texture.h>

namespace easy_engine {
	namespace resource {

		class EASY_ENGINE_API Mesh : public Renderable {

			friend class boost::serialization::access;

			typedef float* (*func_ptr_t)(Mesh*);

		public:
			template<class Archive>
			void serialize(Archive& ar, const unsigned int version);

			Eigen::Matrix<float, -1, 3, Eigen::RowMajor> vertices;
			Eigen::Matrix<float, -1, 3, Eigen::RowMajor> vertex_normals;
			Eigen::Matrix<float, -1, 2, Eigen::RowMajor> texture_coords;
			uint32_t vertex_count;
			std::vector<uint32_t> faces;
			ushort_t texture_index = 0;
			ushort_t material_index = 0;
		};
	}
}
#endif // !RENDERABLE_3D_H
