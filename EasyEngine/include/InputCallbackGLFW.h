#pragma once

#include <glfw3.h>

#include <InputManager.h>

class InputCallbackGLFW {
	public: 
		static easy_engine::input_manager::InputManager* input_manager;

		static void MousePosCallback(GLFWwindow* window, double x, double y);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers);
		static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers);
};