#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include <glm/glm.hpp>

namespace easy_engine {
	namespace render_manager {

		class RenderManagerOpenGL;

		class Camera
		{
		public:
			Camera();
		private:
			friend class RenderManagerOpenGL;
			glm::mat4 view_matrix;
		};
	}
}

#endif // !CAMERA_H

