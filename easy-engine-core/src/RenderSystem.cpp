#include <EasyEngine/eepch.h>
#include <EasyEngine/render_manager/RenderSystem.h>
#include <EasyEngine/Logger.h>

namespace easy_engine {
	namespace render_manager {
		RenderSystem::RenderSystem()
		{
		}

		void RenderSystem::Update(float dt)
		{
			EE_CORE_INFO("rendering");
		}
	}
}
