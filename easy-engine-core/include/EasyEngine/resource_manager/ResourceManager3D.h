#ifndef RESOURCE_MANAGER_3D_H
#define RESOURCE_MANAGER_3D_H
#pragma once

#include <EasyEngine/resource_manager/ResourceManager.h>
#include <EasyEngine/ecs/component/MeshComponent.h>
#include <EasyEngine/ecs/component/TextureComponent.h>
#include <EasyEngine/ecs/component/MaterialComponent.h>
#include <EasyEngine/resource/Mesh.h>

namespace easy_engine {

	namespace resource_manager {
		class EASY_ENGINE_API ResourceManager3D : public ResourceManager {
		public:
			ResourceManager3D();
			~ResourceManager3D();
			ResourceManager3D(ResourceManager3D&&);
			ResourceManager3D& operator=(ResourceManager3D&&);

			void Load(
				std::string file_path,
				ecs::component::MeshComponent& mesh_component,
				ecs::component::TextureComponent& texture_component,
				ecs::component::MaterialComponent& material_component
			);
		private:
			struct Impl;
			std::unique_ptr<Impl> p_impl_;

		};
	}
}

#endif RESOURCE_MANAGER_3D_H