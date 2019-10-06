#include <EasyEngine/eepch.h>
#include <EasyEngine/ui/UIRenderManagerOpenGL.h>
#include <EasyEngine/window_manager/IWindowManager.h>
#include <EasyEngine/event_manager/EventManager.h>

#include <GL/glew.h>
#include <GL/GLU.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL4_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include <nuklear.h>
#include <nuklear_glfw_gl4.h>

namespace easy_engine {
	namespace ui {

		constexpr int MAX_VERTEX_BUFFER = 512 * 1024;
		constexpr int MAX_ELEMENT_BUFFER = 128 * 1024;

		struct UIRenderManagerOpenGL::Impl {
			nk_context* context;
			std::shared_ptr<window_manager::IWindowManager> window_manager;

			Impl(std::shared_ptr<window_manager::IWindowManager> window_manager_)
				: window_manager(window_manager_) {}

			auto SetupContext() -> void {
				auto window = static_cast<GLFWwindow*>(this->window_manager->GetWindow());
				this->context = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
				struct nk_font_atlas* atlas;
				nk_glfw3_font_stash_begin(&atlas);
				nk_glfw3_font_stash_end();
			}
		};

		UIRenderManagerOpenGL::UIRenderManagerOpenGL(
			std::shared_ptr<window_manager::IWindowManager> window_manager,
			std::shared_ptr<event_manager::EventManager> event_manager
		)
			: p_impl_(new Impl(window_manager)) {
			event_manager->Subscribe(event_manager::EventType::kWindowCreated, this);
			event_manager->Subscribe(event_manager::EventType::kRender, this);
		}

		auto UIRenderManagerOpenGL::Render() -> void {

		}

		auto UIRenderManagerOpenGL::OnEvent(event_manager::Event event) -> void {
			switch (event.event_type) {
			case event_manager::EventType::kWindowCreated:
			{
				this->p_impl_->SetupContext();
				break;
			}
			case event_manager::EventType::kRender:
			{
				nk_glfw3_render(NK_ANTI_ALIASING_ON);
				break;
			}
			}
		}

		auto UIRenderManagerOpenGL::GetContext() -> void* {
			return this->p_impl_->context;
		}


	}
}