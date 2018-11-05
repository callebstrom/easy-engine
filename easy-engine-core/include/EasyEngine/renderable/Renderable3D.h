#ifndef RENDERABLE_3D_H
#define RENDERABLE_3D_H
#pragma once

#include <Eigen/Core>
#include <boost/scoped_ptr.hpp>

#include <EasyEngine/renderable/Renderable.h>
#include <EasyEngine/renderable/Texture.h>

namespace easy_engine {
	namespace renderable {

		class EASY_ENGINE_API Renderable3D : public Renderable {

			friend class boost::serialization::access;

			typedef float*(*func_ptr_t)(Renderable3D*);

			public:
				float* GetVertexNormalArray(func_ptr_t compute_normals_func);
				uint32_t GetVertexCount() { return this->vertex_count_; };
				Eigen::Matrix<float, -1, 3, Eigen::RowMajor> GetVertices() { return this->vertices_; };
				Eigen::MatrixX3f GetVertexNormals() { return this->vertex_normals_; };
				std::vector<ushort_t> GetFaces() { return this->faces_; };
				std::vector<ushort_t> GetVertexIndices() { return this->vertex_indices_; };
				std::shared_ptr<Texture> GetTexture() { return this->texture_; }

				void SetVertexCount(uint32_t vertex_count) { this->vertex_count_ = vertex_count; };
				void SetVertices(Eigen::Matrix<float, -1, 3, Eigen::RowMajor> vertices) { this->vertices_ = vertices; };
				void SetVertexIndices(std::vector<ushort_t> vertex_indices) { this->vertex_indices_ = vertex_indices; };
				void SetTexture(Texture* texture) { this->texture_ = std::shared_ptr<Texture>(texture); }
				template<class Archive>
				void serialize(Archive & ar, const unsigned int version);
			private:
				uint32_t vertex_count_;
				Eigen::Matrix<float, -1, 3, Eigen::RowMajor> vertices_;
				Eigen::MatrixX3f vertex_normals_;
				std::vector<ushort_t> faces_;
				std::vector<ushort_t> vertex_indices_;
				std::shared_ptr<Texture> texture_;
		};
	}
}
#endif // !RENDERABLE_3D_H
