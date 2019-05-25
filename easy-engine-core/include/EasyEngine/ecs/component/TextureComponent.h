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
			class TextureComponent : public Component {
			public:
				resource::Texture* texture;
			};
		}
	}
}

#endif // !TEXTURE_COMPONENT_H

