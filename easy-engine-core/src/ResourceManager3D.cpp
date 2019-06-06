#include <EasyEngine/eepch.h>

#include <Eigen/Core>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <EasyEngine/Logger.h>
#include <EasyEngine/resource_manager/ResourceManager3D.h>

namespace easy_engine {
	namespace resource_manager {
		struct ResourceManager3D::Impl {
			Assimp::Importer importer;

			Eigen::Matrix<float, -1, 3, Eigen::RowMajor> ExtractVertices(aiMesh* mesh) {
				Eigen::Matrix<float, -1, 3, Eigen::RowMajor> vertices;
				vertices.conservativeResize(mesh->mNumVertices, Eigen::NoChange);
				auto test = mesh->mNumVertices;

				for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
					Eigen::Vector3f vec;
					vec << mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z;
					vertices.row(i) = vec;
				}

				return vertices;
			}

			std::vector<uint32_t> ExtractFaces(aiMesh* mesh) {
				std::vector<uint32_t> faces;
				if (!mesh->HasFaces()) return faces;

				for (uint32_t i = 0; i < mesh->mNumFaces; ++i) {
					const auto face = &mesh->mFaces[i];
					// Assume triangles (aiProcess_Triangulate)
					faces.push_back(face->mIndices[0]);
					faces.push_back(face->mIndices[1]);
					faces.push_back(face->mIndices[2]);
				}

				return faces;
			}

			Eigen::Matrix<float, -1, 3, Eigen::RowMajor> ExtractNormals(aiMesh* mesh) {
				Eigen::Matrix<float, -1, 3, Eigen::RowMajor> normals;
				normals.conservativeResize(mesh->mNumVertices, Eigen::NoChange);

				for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
					Eigen::Vector3f vec;
					vec << mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z;
					normals.row(i) = vec;
				}

				return normals;
			}
		};

		void ResourceManager3D::Load(std::string file_path, ecs::component::MeshComponent& mesh_component) {
			auto scene = this->p_impl_->importer.ReadFile(
				file_path.c_str(),
				aiProcess_Triangulate |
				aiProcess_GenNormals
			);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
				EE_CORE_ERROR("Could not load scene: ", this->p_impl_->importer.GetErrorString());
				return;
			}

			// Create a submesh for each mesh found in imported scene
			for (uint32_t i = 0; i < scene->mNumMeshes; i++) {
				const auto mesh_ = scene->mMeshes[i];
				auto mesh = new resource::Mesh();

				mesh->name = file_path + "_" + std::to_string(i);

				mesh->vertex_count = mesh_->mNumVertices;
				mesh->vertices = this->p_impl_->ExtractVertices(mesh_);
				mesh->faces = this->p_impl_->ExtractFaces(mesh_);
				mesh->vertex_normals = this->p_impl_->ExtractNormals(mesh_);

				mesh_component.sub_meshes->push_back(mesh);
			}
		}

		ResourceManager3D::ResourceManager3D()
			: p_impl_(std::make_unique<Impl>()) {}

		ResourceManager3D::~ResourceManager3D() = default;
		ResourceManager3D::ResourceManager3D(ResourceManager3D&&) = default;
		ResourceManager3D& ResourceManager3D::operator=(ResourceManager3D&&) = default;
	}
}
