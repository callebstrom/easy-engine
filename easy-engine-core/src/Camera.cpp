#include <EasyEngine/eepch.h>
#include <EasyEngine/render_manager/Camera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace easy_engine {
	namespace render_manager {

		Camera::Camera()
			: position(glm::vec3(0.f, 5.f, 3.f))
		{
			// static double lastTime = glfwGetTime();
			// double currentTime = glfwGetTime();
			// float deltaTime = float(currentTime - lastTime);

			glm::vec3 origin = glm::vec3(0.f, 0.f, 0.f);

			// horizontal angle : toward -Z
			float horizontalAngle = glm::radians(180.0f);

			// vertical angle : 0, look at the horizon
			float verticalAngle = 0.0f;

			// static const float mouseSpeed = 0.1f;

			// horizontalAngle += mouseSpeed * deltaTime * float(boost::lexical_cast<int>(this->p_impl_->render_config_->Get(configuration::RenderConfigurationParams::RESOLUTION_X)) / 2 - x);
			// verticalAngle += mouseSpeed * deltaTime * float(boost::lexical_cast<int>(this->p_impl_->render_config_->Get(configuration::RenderConfigurationParams::RESOLUTION_Y)) / 2 - y);

			glm::vec3 direction = glm::vec3(
				cos(verticalAngle) * sin(horizontalAngle),
				sin(verticalAngle),
				cos(verticalAngle) * cos(horizontalAngle)
			);

			// Right vector
			glm::vec3 right = glm::vec3(
				sin(horizontalAngle - glm::radians(180.0f) / 2.0f),
				0,
				cos(horizontalAngle - glm::radians(180.0f) / 2.0f)
			);

			// Up vector : perpendicular to both direction and right
			glm::vec3 up = glm::cross(right, direction);

			// Camera matrix
			this->view_matrix = glm::lookAt(
				this->position,				// Camera is here
				this->position + direction,	// and looks here : at the same position, plus "direction"
				up						// Head is up (set to 0,-1,0 to look upside-down)
			);
		}
	}
}

