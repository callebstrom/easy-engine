#pragma once

#include <GL/glfw3.h>

#include <EasyEngine/input_manager/InputManager.h>

class EASY_ENGINE_API InputCallbackGLFW {
	public: 
		static easy_engine::input_manager::InputManager* input_manager;

		static void MousePosCallback(GLFWwindow* window, double x, double y);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers);
		static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers);
};