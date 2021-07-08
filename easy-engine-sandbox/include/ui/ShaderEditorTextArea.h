#pragma once

#include <EasyEngine/Lifecycle.h>
#include <EasyEngine/world/World.h>
#include <EasyEngine/shader_manager/IShaderManager.h>

namespace easy_engine {
	class ShaderEditorTextArea : public lifecycle::IOnInit {
		public:
			ShaderEditorTextArea(world::World* world, Ref<shader_manager::IShaderManager> shader_manager);
			void OnInit() override;
	};
}
