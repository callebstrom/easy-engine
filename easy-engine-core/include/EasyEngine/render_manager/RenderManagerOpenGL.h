#pragma once

#include <EasyEngine/event_manager/IObserver.h>
#include <EasyEngine/render_manager/IRenderManager.h>
#include <EasyEngine/resource/Mesh.h>
#include <EasyEngine/shader_manager/ShaderPipeline.h>

#ifdef DLLDIR_EX
#include <EasyEngine/Logger.h>
#endif

namespace easy_engine {

namespace shader_manager {
class ShaderManagerOpenGL;
}

using shader_manager::ShaderManagerOpenGL;

namespace render_manager {

class EASY_ENGINE_API RenderManagerOpenGL : public IRenderManager,
                                            public event_manager::IObserver {
 public:
  RenderManagerOpenGL(configuration::RenderConfiguration_t* rc,
                      std::shared_ptr<ShaderManagerOpenGL> shader_manager);
  ~RenderManagerOpenGL();

  void Render(resource::Mesh* mesh, Eigen::Matrix4f model_matrix,
              std::vector<resource::Texture*> textures,
              resource::Material* material) override;
  void Render(resource::PointLight point_light,
              Eigen::Vector3f translation) override;
  void Render(resource::DirectionalLight directional_light,
              Eigen::Vector3f translation) override;
  void UpdateCameraAngle(double x, double y) override;
  void SetShaderPipeline(
      Ref<shader_manager::ShaderPipeline> shader_pipeline) override;
  void OnEvent(event_manager::Event event) override;

 private:
  struct Impl;
  struct Light;
  std::unique_ptr<Impl> p_impl_;
};
}  // namespace render_manager
}  // namespace easy_engine
