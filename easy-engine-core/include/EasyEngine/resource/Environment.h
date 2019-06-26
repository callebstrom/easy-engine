#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#pragma once

#include <EasyEngine/resource/Light.h>
#include <EasyEngine/resource/Camera.h>

namespace easy_engine {

	namespace render_manager {
		class RenderManagerOpenGL;
	}

	namespace resource {
		class EASY_ENGINE_API Environment {
		public:
			Environment() = default;
			virtual ~Environment() = default;

			void AddLight(const PointLight& light) { this->point_lights.push_back(light); }
			void AddLight(const DirectionalLight& light) { this->directional_lights.push_back(light); }
			void AddLight(const SpotLight& light) { this->spot_lights.push_back(light); }

		private:
			friend class render_manager::RenderManagerOpenGL;
			std::vector<PointLight> point_lights;
			std::vector<DirectionalLight> directional_lights;
			std::vector<SpotLight> spot_lights;
		};
	}
}

#endif // !ENVIRONMENT_H

