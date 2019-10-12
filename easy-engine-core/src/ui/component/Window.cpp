#include <EasyEngine/eepch.h>
#include <EasyEngine/ui/component/WindowComponent.h>

#include <nuklear.h>

namespace easy_engine {
	namespace ui {
		namespace component {

			auto WindowComponent::End() -> void {
				/*nk_begin(
					this->p_impl_->context,
					this->p_impl_->title.c_str(),
					nk_rect(50, 50, this->p_impl_->width, this->p_impl_->height),
					NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
					NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE
				);
				auto& children = this->p_impl_->children_;
				while (!children.empty()) {
					children.front()->End();
					children.pop();
				}
				nk_end(this->p_impl_->context);*/
			}
		}
	}
}