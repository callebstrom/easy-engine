#include <EasyEngine/input_manager/InputManager.h>
#include <EasyEngine/ManagerLocator.h>

namespace easy_engine {
	namespace input_manager {

		void InputManager::HandleMouseButtonPress(int button, int modifier) {

		}

		void InputManager::HandleMouseButtonRelease(int button, int modifier) {

		}

		void InputManager::PollEvents() {
			glfwPollEvents();
		}

		void InputManager::HandleMousePosUpdate(double x, double y) {
			/**
			* TODO Forward behaviour to RenderManagerOpenGL::UpdateCameraAngle in some clever way..
			*
			* Best solution is probably to express the mvp in UpdateCameraAngle as an Eigen equivalent of glm::mat4 and put all 
			* camera stuff in a generic Camera3D class. The Camera3D class could then have callbacks registered for "onCameraUpdate".
			* E.g. RenderManagerOpenGL::UpdateCameraAngle is an callback for onCameraUpdate, and takes only an Eigen equivalent of glm::mat4 as arg, 
			* and the Camera3D class is responsible for generating the model view projection matrix and calling the callback. 
			* HandleMousePosUpdate is only responsible for forwarding, and possibly inversing the mouse position.
			*/
			ManagerLocator::render_manager->UpdateCameraAngle(x, y);
		}
	
	}
}