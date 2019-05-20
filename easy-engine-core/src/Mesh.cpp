#include <EasyEngine/eepch.h>
#include <EasyEngine/resource/Mesh.h>
#include <EasyEngine/render_manager/RenderManagerOpenGL.h>

namespace easy_engine {
	namespace resource {

		float* Mesh::GetVertexNormalArray(func_ptr_t compute_normals_func) {
			return compute_normals_func(this);
		}

		template<class Archive>
		void Mesh::serialize(Archive& archive, const unsigned int version) {

			archive& boost::serialization::base_object<Renderable>(*this);
			archive& this->faces_;
			archive& this->name;
			archive& this->vertex_count_;
			archive& this->vertex_indices_;
			archive& this->vertex_normals_;
			archive& this->vertices_;
		}
	}
}