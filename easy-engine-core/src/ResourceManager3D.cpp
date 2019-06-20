#include <EasyEngine/eepch.h>

#include <filesystem>

#include <Eigen/Core>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/std_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <EasyEngine/Logger.h>
#include <EasyEngine/resource_manager/ResourceManager3D.h>
#include <EasyEngine/resource/Texture.h>
#include <EasyEngine/resource/Material.h>
#include <EasyEngine/resource/Bone.h>

namespace easy_engine {
	namespace resource_manager {

		typedef std::string ResourceLocation;

		template<typename CachableType>
		class ResourceCache {
		public:
			bool HasResource(ResourceLocation resource_location) {
				return this->cache.find(resource_location) != cache.end();
			}

			CachableType GetResource(ResourceLocation resource_location) {
				return this->cache[resource_location];
			}

			void Cache(ResourceLocation resource_location, CachableType cachable) {
				this->cache[resource_location] = cachable;
			}
		private:
			std::map<ResourceLocation, CachableType> cache;
		};

		struct ResourceManager3D::Impl {

			Assimp::Importer importer;
			ResourceCache<resource::Texture*> texture_cache;

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

			Eigen::Matrix<float, -1, 2, Eigen::RowMajor> ExtractUVs(aiMesh* mesh) {
				Eigen::Matrix<float, -1, 2, Eigen::RowMajor> uvs;
				uvs.conservativeResize(mesh->mNumVertices, Eigen::NoChange);

				for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
					Eigen::Vector2f vec;
					vec << mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y;
					uvs.row(i) = vec;
				}

				return uvs;
			}

			std::vector<resource::Bone> ExtractBones(aiMesh* mesh) {
				/*for (uint32_t i = 0; i < mesh->mNumBones; i++) {
					uint32_t bone_index = 0;
					std::string bone_name(mesh->mBones[i]->mName.data);

					if (m_BoneMapping.find(BoneName) == m_BoneMapping.end()) {
						BoneIndex = m_NumBones;
						m_NumBones++;
						BoneInfo bi;
						m_BoneInfo.push_back(bi);
					}
					else {
						BoneIndex = m_BoneMapping[BoneName];
					}

					m_BoneMapping[BoneName] = BoneIndex;
					m_BoneInfo[BoneIndex].BoneOffset = pMesh->mBones[i]->mOffsetMatrix;

					for (uint j = 0; j < pMesh->mBones[i]->mNumWeights; j++) {
						uint VertexID = m_Entries[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
						float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
						Bones[VertexID].AddBoneData(BoneIndex, Weight);
					}
				}*/
			}

			resource::Texture* LoadCompressedImageFromMemory(void* data, size_t size) {
				auto texture = new resource::Texture();

				int width, height, bpp;
				unsigned char* decompressed_pixel_data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(data), size, &width, &height, &bpp, 4);

				texture->width = width;
				texture->height = height;
				texture->bpp = bpp;
				texture->raw = decompressed_pixel_data;

				return texture;
			}

			resource::Texture* LoadImageFromFile(std::string path) {
				auto texture = new resource::Texture();

				int width, height, bpp;

				unsigned char* decompressed_pixel_data = stbi_load(path.c_str(), &width, &height, &bpp, 0);
				auto failure = stbi_failure_reason();

				texture->file_path = path;
				texture->width = width;
				texture->height = height;
				texture->bpp = bpp;
				texture->raw = decompressed_pixel_data;

				return texture;
			}

			void LoadEmbeddedTexture(const aiScene* scene, const aiMesh* mesh_, ecs::component::TextureComponent& texture_component, size_t& type_index, resource::TextureType texture_type) {
				aiString* texture_index_buffer = new aiString;

				aiGetMaterialTexture(scene->mMaterials[mesh_->mMaterialIndex], (aiTextureType)texture_type, 0, texture_index_buffer, 0, 0, 0, 0, 0, 0);

				static const uint32_t ASCII_OFFSET = 48;
				auto texture_index = (uint32_t)texture_index_buffer->data[1] - ASCII_OFFSET;


				std::string cache_key = mesh_->mName.C_Str() + std::to_string(texture_index);
				if (texture_cache.HasResource(cache_key)) {
					type_index = std::distance(
						texture_component.textures->begin(),
						std::find(
							texture_component.textures->begin(),
							texture_component.textures->end(),
							texture_cache.GetResource(cache_key)
						)
					);
					return;
				}

				if (texture_index > 0 && scene->mNumTextures >= texture_index) {

					auto texture_ = scene->mTextures[texture_index];

					resource::Texture* texture;

					// If mHeight is 0 we should use stbi_load_from_memory as this is then not pixel data
					if (texture_->mHeight == 0) {
						size_t buffer_size = texture_->mWidth;
						texture = this->LoadCompressedImageFromMemory(texture_->pcData, buffer_size);
					}
					else {
						texture = new resource::Texture();
						texture->width = texture_->mWidth;
						texture->height = texture_->mHeight;
						texture->raw = reinterpret_cast<byte*>(texture_->pcData);
					}
					texture_component.textures->push_back(texture);
					type_index = texture_component.textures->size() - 1;

					this->texture_cache.Cache(cache_key, texture);
				}
			}

			void LoadExternalTexture(std::string mesh_path, const aiScene* scene, const aiMesh* mesh_, ecs::component::TextureComponent& texture_component, size_t& type_index, resource::TextureType texture_type) {

				auto texture_index_buffer = new aiString;

				aiGetMaterialTexture(scene->mMaterials[mesh_->mMaterialIndex], (aiTextureType)texture_type, 0, texture_index_buffer, 0, 0, 0, 0, 0, 0);
				if (texture_index_buffer->length > 0) {
					const std::filesystem::path path = std::string(texture_index_buffer->C_Str());

					const std::string texture_path = path.is_relative()
						? mesh_path.substr(0, mesh_path.find_last_of('\\') + 1) + path.string()
						: path.string();

					if (texture_cache.HasResource(texture_path)) {
						type_index = std::distance(
							texture_component.textures->begin(),
							std::find(
								texture_component.textures->begin(),
								texture_component.textures->end(),
								texture_cache.GetResource(texture_path)
							)
						);
						return;
					}

					auto texture = this->LoadImageFromFile(texture_path);
					texture_component.textures->push_back(texture);
					type_index = texture_component.textures->size() - 1;

					this->texture_cache.Cache(texture_path, texture);
				}
			}

		};

		void ResourceManager3D::Load(
			std::string file_path,
			ecs::component::MeshComponent& mesh_component,
			ecs::component::TextureComponent& texture_component,
			ecs::component::MaterialComponent& material_component
		) {
			auto scene = this->p_impl_->importer.ReadFile(
				file_path.c_str(),
				aiProcess_Triangulate |
				aiProcess_GenNormals |
				aiProcess_FlipUVs
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
				mesh->texture_coords = this->p_impl_->ExtractUVs(mesh_);

				mesh->material_index = i;

				mesh_component.sub_meshes->push_back(mesh);

				if (scene->mNumMaterials >= mesh_->mMaterialIndex + 1) {
					auto material_ = scene->mMaterials[mesh_->mMaterialIndex];
					auto material = new resource::Material();

					aiColor3D diffuse_color, specular_color;
					material_->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse_color);
					material_->Get(AI_MATKEY_COLOR_SPECULAR, specular_color);

					float shininess;
					material_->Get(AI_MATKEY_SHININESS, shininess);

					material->diffuse_color = Eigen::Vector3f(diffuse_color.r, diffuse_color.g, diffuse_color.b);
					material->specular_color = Eigen::Vector3f(specular_color.r, specular_color.g, specular_color.b);
					material->shininess = shininess;
					material_component.materials->push_back(material);

					// Handle embedded textures
					if (scene->HasTextures()) {
						EE_CORE_TRACE("Mesh has embedded texture");
						this->p_impl_->LoadEmbeddedTexture(scene, mesh_, texture_component, material->diffuse_texture_index, resource::TextureType::DIFFUSE);
						this->p_impl_->LoadEmbeddedTexture(scene, mesh_, texture_component, material->specular_texture_index, resource::TextureType::SPECULAR);
					}
					else {
						EE_CORE_TRACE("Mesh has external texture");
						this->p_impl_->LoadExternalTexture(file_path, scene, mesh_, texture_component, material->diffuse_texture_index, resource::TextureType::DIFFUSE);
						this->p_impl_->LoadExternalTexture(file_path, scene, mesh_, texture_component, material->specular_texture_index, resource::TextureType::SPECULAR);
					}
				}
			}
		}

		ResourceManager3D::ResourceManager3D()
			: p_impl_(std::make_unique<Impl>()) {}

		ResourceManager3D::~ResourceManager3D() = default;
		ResourceManager3D::ResourceManager3D(ResourceManager3D&&) = default;
		ResourceManager3D& ResourceManager3D::operator=(ResourceManager3D&&) = default;
	}
}
