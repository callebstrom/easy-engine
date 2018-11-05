#include <EasyEngine/window_manager/InputCallbackGLFW.h>

easy_engine::input_manager::InputManager* InputCallbackGLFW::input_manager = NULL;

void InputCallbackGLFW::MousePosCallback(GLFWwindow* window, double x, double y) {
	input_manager->HandleMousePosUpdate(x, y);
};

void InputCallbackGLFW::MouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers) {
	if (action == GLFW_PRESS) {
		input_manager->HandleMouseButtonPress(button, modifiers);
	} else if (action == GLFW_RELEASE) {
		input_manager->HandleMouseButtonRelease(button, modifiers);
	}
};

void InputCallbackGLFW::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers) {

};