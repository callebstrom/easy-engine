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

		void ResourceManager3D::LoadObj(std::string path_relative_to_base, renderable::Renderable3D &dest)
		{

			std::ifstream ifs(base_path_ + path_relative_to_base);
			if (!ifs.is_open()) {
				std::cout << "Failed to open file " + path_relative_to_base;
			}
			std::string line;
			std::string fileString;
			int vertex_index = 0;

			while (std::getline(ifs, line)) {
				std::stringstream string_stream_outer(line.c_str());

				// read the first word of the line
				std::string first_word;
				string_stream_outer >> first_word;

				// If obj vertex annotation
				if (strcmp(first_word.c_str(), "v") == 0) {
					__int64 current_index = dest.vertices_.rows();
					std::stringstream string_stream_inner(line.c_str());
					std::string v, x, y, z;

					string_stream_inner >> v >> x >> y >> z;

					Eigen::Vector3f vec;
					// TODO we lose precision here due to double, implement Boost c++ library 
					vec << (float)std::atof(x.c_str()), (float)std::atof(y.c_str()), (float)std::atof(z.c_str());

					dest.vertices_.conservativeResize(dest.vertices_.rows() + 1, Eigen::NoChange);
					dest.vertices_.row(dest.vertices_.rows() - 1) = vec;
				}
			}
		}
	}
}
