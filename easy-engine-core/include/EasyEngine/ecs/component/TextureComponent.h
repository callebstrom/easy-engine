#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H
#pragma once

#include <EasyEngine/ecs/component/Component.h>

namespace easy_engine {

	namespace resource {
		class Texture;
	}

	namespace ecs {
		namespace component {
			class EASY_ENGINE_API TextureComponent : public Component {
			public:
				std::vector<resource::Texture*>* textures = new std::vector<resource::Texture*>();
			};
		}
	}
}

#endif // !TEXTURE_COMPONENT_H

