#ifndef _3D_OBJECT_RENDERABLE_H
#define _3D_OBJECT_RENDERABLE_H
#pragma once

#include <EasyEngine/ecs/component/TransformComponent.h>

namespace easy_engine {

	namespace ecs {
		namespace component {
			class MeshComponent;
		}
	}

	namespace render_manager {
		struct _3DObjectRenderable {
			ecs::component::TransformComponent* transform_component = new ecs::component::TransformComponent();
			ecs::component::MeshComponent* mesh_component;
		};
	}
}

#endif // !3D_OBJECT_RENDERABLE_H

