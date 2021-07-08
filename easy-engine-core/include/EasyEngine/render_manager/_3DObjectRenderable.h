#pragma once

#include <EasyEngine/ecs/component/TransformComponent.h>

namespace easy_engine {

	namespace ecs {
		namespace component {
			class MeshComponent;
			class TextureComponent;
			class MaterialComponent;
		}
	}

	namespace render_manager {
		struct _3DObjectRenderable {
			Ref<ecs::component::TransformComponent> transform_component = CreateRef<ecs::component::TransformComponent>();
			Ref<ecs::component::MeshComponent> mesh_component;
			std::optional<Ref<ecs::component::TextureComponent>> texture_component;
			std::optional<Ref<ecs::component::MaterialComponent>> material_component;
			bool has_textures = false;
			bool has_materials = false;
		};
	}
}

