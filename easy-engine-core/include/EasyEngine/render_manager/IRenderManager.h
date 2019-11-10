#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#pragma once

#include <Eigen/Core>

#include <EasyEngine/resource/Renderable.h>
#include <EasyEngine/resource/Mesh.h>
#include <EasyEngine/resource/Material.h>
#include <EasyEngine/configuration/RenderConfiguration.h>
#include <EasyEngine/resource/Light.h>
#include <EasyEngine/Common.h>

namespace easy_engine {

	namespace shader_manager {
		class ShaderPipeline;
	}

	namespace render_manager {
		class EASY_ENGINE_API IRenderManager {
		public:
			virtual void Render(resource::Mesh* mesh, Eigen::Matrix4f model_matrix, std::vector<resource::Texture*> textures, resource::Material* material) = 0;
			virtual void Render(resource::Light* light, Eigen::Vector3f translation) = 0;
			virtual void UpdateCameraAngle(double x, double y) = 0;
			virtual void SetShaderPipeline(Ref<shader_manager::ShaderPipeline> shader_pipeline) = 0;
			virtual ~IRenderManager() = default;
		};
	}
}
#endif // !RENDER_MANAGER_H
