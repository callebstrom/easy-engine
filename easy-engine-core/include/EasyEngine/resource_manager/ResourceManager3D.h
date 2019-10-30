#ifndef RESOURCE_MANAGER_3D_H
#define RESOURCE_MANAGER_3D_H
#pragma once

#include <EasyEngine/resource_manager/ResourceManager.h>
#include <EasyEngine/ecs/component/MeshComponent.h>
#include <EasyEngine/ecs/component/TextureComponent.h>
#include <EasyEngine/ecs/component/MaterialComponent.h>
#include <EasyEngine/resource/Mesh.h>

#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#include <boost/thread/future.hpp>

namespace easy_engine {

	namespace resource {
		class Material;
		class Texture;
		class Mesh;
	}

	namespace resource_manager {

		const ushort_t NONE = 1;
		const ushort_t LOAD_TEXTURES = 2;
		const ushort_t LOAD_MATERIALS = 4;
		const ushort_t DEFAULT = LOAD_TEXTURES | LOAD_MATERIALS;


		class ResourceCollection {
		public:
			std::vector<resource::Material*> materials;
			std::vector<resource::Texture*> textures;
			std::vector<resource::Mesh*> meshes;
		};

		using LoadFuture = boost::future<resource_manager::ResourceCollection>;

		class EASY_ENGINE_API ResourceManager3D {
		public:
			ResourceManager3D();
			~ResourceManager3D();
			ResourceManager3D(ResourceManager3D&&);
			ResourceManager3D& operator=(ResourceManager3D&&);
			auto Load(
				std::string file_path,
				ushort_t flags
			) -> LoadFuture;
		private:
			struct Impl;
			std::unique_ptr<Impl> p_impl_;
		};
	}
}

#endif RESOURCE_MANAGER_3D_H