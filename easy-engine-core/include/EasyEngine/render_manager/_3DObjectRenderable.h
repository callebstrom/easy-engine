#ifndef _3D_OBJECT_RENDERABLE_H
#define _3D_OBJECT_RENDERABLE_H
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
			ecs::component::TransformComponent* transform_component = new ecs::component::TransformComponent();
			ecs::component::MeshComponent* mesh_component;
			ecs::component::TextureComponent* texture_component;
			ecs::component::MaterialComponent* material_component;
			bool has_textures = false;
			bool has_materials = false;
		};
	}
}

#endif // !3D_OBJECT_RENDERABLE_H

