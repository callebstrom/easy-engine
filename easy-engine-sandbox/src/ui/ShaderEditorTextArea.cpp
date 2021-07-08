#include <EasyEngine/eepch.h>
#include <ui/ShaderEditorTextArea.h>

/*easy_engine::ShaderEditorTextArea::ShaderEditorTextArea(world::World* world, Ref<shader_manager::IShaderManager> shader_manager)
{
}*/

void easy_engine::ShaderEditorTextArea::OnInit()
{
	/*auto shader_editor_window = world->CreateEntity();
	auto window_component = ui::component::WindowComponent();
	window_component.height = 800;
	window_component.width = 600;
	window_component.title = "Shader editor";
	ecs::component::TransformComponent shader_editor_transform_component;
	shader_editor_transform_component.Translation(100, 100, 0);

	world->AddComponent<ecs::component::TransformComponent>(shader_editor_window, shader_editor_transform_component);
	world->AddComponent<ui::component::WindowComponent>(shader_editor_window, window_component);

	auto text_area = world->CreateEntity();
	auto pixel_shader = this->shader_manager->GetAttachedPipeline()->GetPixelShader();
	auto source = pixel_shader->GetSource();
	auto text_area_component = ui::component::TextAreaComponent(800, 2000, 40000, source);
	ecs::component::TransformComponent text_area_transform_component;
	ecs::component::ParentEntityComponent window_parent_component;
	window_parent_component.entity = shader_editor_window.entity;

	world->AddComponent<ecs::component::TransformComponent>(text_area, text_area_transform_component);
	world->AddComponent<ui::component::TextAreaComponent>(text_area, text_area_component);
	world->AddComponent<ecs::component::ParentEntityComponent>(text_area, window_parent_component);*/
};
