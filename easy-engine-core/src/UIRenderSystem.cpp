#include <EasyEngine/eepch.h>
#include <GL/glew.h>

#include <EasyEngine/ui/IUIRenderManager.h>
#include <EasyEngine/ui/UIRenderSystem.h>
#include <EasyEngine/ui/IContext.h>
#include <EasyEngine/ui/component/WindowComponent.h>
#include <EasyEngine/ui/component/TextAreaComponent.h>
#include <EasyEngine/ecs/component/TransformComponent.h>
#include <EasyEngine/ecs/component/ParentEntityComponent.h>
#include <EasyEngine/Common.h>
#include <EasyEngine/world/World.h>
#include <EasyEngine/Logger.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/graphviz.hpp>

#include <nuklear.h>
#include <nuklear_glfw_gl4.h>

namespace easy_engine {
	namespace ui {

		struct Vertex {
			entity::Entity* entity;
		};

		struct Edge { std::string name; };

		using EntityID = float;
		using UIGraph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, Vertex, Edge>;
		using VertexIterator = boost::graph_traits<UIGraph>::vertex_iterator;
		using VertexDescriptor = boost::graph_traits<UIGraph>::vertex_descriptor;

		class UIGraphVisitor : public boost::default_dfs_visitor {
		public:

			UIGraphVisitor(world::World* world)
				: world_(world) {}

			void start_vertex(VertexDescriptor vertex_descriptor, const UIGraph& graph) const {
				auto entity = graph[vertex_descriptor].entity;

				auto maybe_window_component = this->world_->GetComponentForEntity<ui::component::WindowComponent>(entity);
				auto maybe_text_area_component = this->world_->GetComponentForEntity<ui::component::TextAreaComponent>(entity);
				EE_CORE_TRACE("start");
			}

			void finish_vertex(VertexDescriptor vertex_descriptor, const UIGraph& graph) const {
				auto entity = graph[vertex_descriptor].entity;

				auto maybe_window_component = this->world_->GetComponentForEntity<ui::component::WindowComponent>(entity);
				auto maybe_text_area_component = this->world_->GetComponentForEntity<ui::component::TextAreaComponent>(entity);
				EE_CORE_TRACE("end");
			}
		private:
			world::World* world_;
		};

		struct UIRenderSystem::Impl {

			Impl(std::shared_ptr<IUIRenderManager> ui_render_manager_)
				: ui_render_manager(ui_render_manager_) {}

			std::shared_ptr<IUIRenderManager> ui_render_manager;

			auto FindVertex(UIGraph ui_graph, Vertex vertex) -> std::optional<VertexDescriptor> {
				VertexIterator vertex_iterator, vertex_iterator_end;
				for (boost::tie(vertex_iterator, vertex_iterator_end) = vertices(ui_graph); vertex_iterator != vertex_iterator_end; ++vertex_iterator) {
					if (ui_graph[*vertex_iterator].entity == vertex.entity) return *vertex_iterator;
				}
				return std::optional<VertexDescriptor>();
			}

			auto BuildUITree(world::World* world, std::vector<entity::Entity*> entities, UIGraph ui_graph = UIGraph(0)) -> UIGraph {
				if (entities.size() == 0) {
					return ui_graph;
				}

				const auto entity = entities.back();
				entities.pop_back();
				auto maybe_parent_entity_component = world->GetComponentForEntity<ecs::component::ParentEntityComponent>(entity);

				// TODO predicate does not work
				auto child_already_in_graph = FindVertex(ui_graph, {entity});

				if (maybe_parent_entity_component.has_value()) {
					auto parent_entity = maybe_parent_entity_component.value()->entity;

					// TODO predicate does not work
					auto parent_already_in_graph = FindVertex(ui_graph, {parent_entity});

					auto child_node = child_already_in_graph.has_value() ? child_already_in_graph.value() : boost::add_vertex({entity}, ui_graph);

					auto parent_node = parent_already_in_graph.has_value() ? parent_already_in_graph.value() : boost::add_vertex({parent_entity}, ui_graph);
					boost::add_edge(child_node, parent_node, {"child"}, ui_graph);
				}
				else if (!child_already_in_graph.has_value()) {
					boost::add_vertex({entity}, ui_graph);
				}

				return BuildUITree(world, entities, ui_graph);
			}

			void VisitUIGraph(UIGraph ui_graph, world::World* world) {
				std::vector<VertexDescriptor> topological_sort_asc;
				boost::topological_sort(ui_graph, std::back_inserter(topological_sort_asc));

				std::vector<VertexDescriptor> topological_sort_desc;
				boost::topological_sort(ui_graph, std::back_inserter(topological_sort_desc));

				for (auto const& vertex_descriptor : topological_sort_asc) {
					auto vertex = ui_graph[vertex_descriptor];
					auto entity = vertex.entity;

					auto maybe_text_area_component = world->GetComponentForEntity<ui::component::TextAreaComponent>(entity);
					auto maybe_window_component = world->GetComponentForEntity<ui::component::WindowComponent>(entity);
					auto maybe_transform_component = world->GetComponentForEntity<ecs::component::TransformComponent>(entity);

					if (maybe_window_component.has_value()) {
						auto window = maybe_window_component.value();
						this->ui_render_manager->WindowBegin(
							window->title,
							window->height,
							window->width
						);
					}
					else if (maybe_text_area_component.has_value()) {
						auto text_area = maybe_text_area_component.value();
						this->ui_render_manager->TextArea(text_area->buffer, &text_area->buffer_size, text_area->height, text_area->width);
					}
				}

				for (auto const& vertex_descriptor : topological_sort_desc) {
					auto vertex = ui_graph[vertex_descriptor];
					auto entity = vertex.entity;

					auto maybe_text_area_component = world->GetComponentForEntity<ui::component::TextAreaComponent>(entity);
					auto maybe_window_component = world->GetComponentForEntity<ui::component::WindowComponent>(entity);
					auto maybe_transform_component = world->GetComponentForEntity<ecs::component::TransformComponent>(entity);

					if (maybe_window_component.has_value()) {
						auto window = maybe_window_component.value();
						this->ui_render_manager->WindowEnd();
					}
				}


			}
		};

		UIRenderSystem::UIRenderSystem(std::shared_ptr<ui::IUIRenderManager> ui_render_manager)
			: p_impl_(new Impl(ui_render_manager)) {}

		auto UIRenderSystem::Update(float dt) -> void {

			nk_glfw3_new_frame();

			std::vector<entity::Entity*> entities_vec;
			entities_vec.assign(this->entities_.begin(), this->entities_.end());

			auto ui_graph = this->p_impl_->BuildUITree(this->world, entities_vec);
			this->p_impl_->VisitUIGraph(ui_graph, this->world);
		}
	}
}