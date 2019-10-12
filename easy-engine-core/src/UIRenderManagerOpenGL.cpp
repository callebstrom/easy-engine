#include <EasyEngine/eepch.h>
#include <GL/glew.h>

#include <EasyEngine/ui/UIRenderManagerOpenGL.h>
#include <EasyEngine/window_manager/IWindowManager.h>
#include <EasyEngine/event_manager/EventManager.h>

#include <EasyEngine/ui/ContextOpenGL.h>

#include <GLFW/glfw3.h>

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

			Impl(std::shared_ptr<window_manager::IWindowManager> window_manager_)
				: window_manager(window_manager_) {}

			auto SetupContext() -> void {
				auto window = static_cast<GLFWwindow*>(this->window_manager->GetWindow());
				this->nk_context = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
				struct nk_font_atlas* atlas;
				nk_glfw3_font_stash_begin(&atlas);
				// struct nk_font* future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);
				nk_glfw3_font_stash_end();
				// struct nk_font_atlas* atlas;
				// nk_glfw3_font_stash_begin(&atlas);
				// struct nk_font* future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);
				// nk_glfw3_font_stash_end();
			}

			std::shared_ptr<window_manager::IWindowManager> window_manager;
			nk_context* nk_context;
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
			nk_glfw3_render(NK_ANTI_ALIASING_ON);
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
				this->Render();
				break;
			}
			}
		}
		auto UIRenderManagerOpenGL::WindowBegin(std::string title, int height, int width) -> void {
			nk_begin(
				this->p_impl_->nk_context,
				title.c_str(),
				nk_rect(50, 50, height, width),
				NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
				NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE
			);

			static char* buffer = new char[250];
			static int* buffer_length = new int;

			nk_edit_string(
				this->p_impl_->nk_context,
				NK_EDIT_ALLOW_TAB|NK_EDIT_ALWAYS_INSERT_MODE|NK_EDIT_MULTILINE|NK_EDIT_SELECTABLE|NK_EDIT_CLIPBOARD,
				buffer,
				buffer_length,
				250,
				nk_filter_default
			);
		}

		auto UIRenderManagerOpenGL::WindowEnd() -> void {
			nk_end(this->p_impl_->nk_context);
		}
	}
}