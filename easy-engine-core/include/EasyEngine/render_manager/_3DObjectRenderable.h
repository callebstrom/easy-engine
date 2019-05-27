#ifndef _3D_OBJECT_RENDERABLE_H
#define _3D_OBJECT_RENDERABLE_H
#pragma once

namespace easy_engine {

	namespace ecs {
		namespace component {
			class MeshComponent;
			class TransformComponent;
		}
	}

	namespace render_manager {
		class _3DObjectRenderable
		{
		public:
			ecs::component::TransformComponent* transform_component;
			ecs::component::MeshComponent* mesh_component;
		};
	}
}

#endif // !3D_OBJECT_RENDERABLE_H

