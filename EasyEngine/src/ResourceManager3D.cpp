#include <ResourceManager3D.h>
#include <iostream>
#include <iomanip>

namespace easy_engine {
	namespace resource_manager {
		ResourceManager3D::ResourceManager3D(std::string base_path_)
		{
			this->base_path_ = base_path_;
		}
		ResourceManager3D::~ResourceManager3D()
		{
		}

		renderable::Renderable3D* ResourceManager3D::LoadObj(std::string path_relative_to_base)
		{
			renderable::Renderable3D* renderable = new renderable::Renderable3D();

			renderable->name = "test";

			std::ifstream ifs(base_path_ + path_relative_to_base);
			if (!ifs.is_open()) {
				std::cout << "Failed to open file " + path_relative_to_base;
			}
			std::string line;
			std::string fileString;
			int vertex_index = 0;
			uint32_t vertex_count = 0;

			while (std::getline(ifs, line)) {
				std::stringstream string_stream_outer(line.c_str());

				std::string first_char;
				string_stream_outer >> first_char;

				// If obj vertex annotation
				if (strcmp(first_char.c_str(), "v") == 0) {
					vertex_count++;
					__int64 current_index = renderable->vertices_.rows();
					std::stringstream string_stream_inner(line.c_str());
					std::string v, x, y, z;

					string_stream_inner >> v >> x >> y >> z;
					
					Eigen::Vector3f vec;
					// TODO we lose precision here due to double, implement Boost c++ library 
					vec << (float)std::atof(x.c_str()), (float)std::atof(y.c_str()), (float)std::atof(z.c_str());

					renderable->vertices_.conservativeResize(renderable->vertices_.rows() + 1, Eigen::NoChange);
					renderable->vertices_.row(renderable->vertices_.rows() - 1) = vec;
				} else if (strcmp(first_char.c_str(), "f") == 0) {
					std::string line_trimmed = line.substr(2);// "1/3/4 3/4/3"

					std::vector<std::string> face_coords;
					boost::split(face_coords, line_trimmed, boost::is_any_of(" ")); // ["1/3/4","3/4/3",...]

					for (auto const& fc : face_coords) {
						std::vector<std::string> face_coords_exploded;
						boost::split(face_coords_exploded, fc, boost::is_any_of("/")); // ["1","3","4",...]
						renderable->faces_.push_back(boost::lexical_cast<short>(face_coords_exploded.at(0)) - 1);
					}
				}
			}

			renderable->vertex_count = vertex_count;

			return renderable;
		}
	}
}
