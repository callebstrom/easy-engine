#include <ResourceManager3D.h>
#include <iostream>

namespace easy_engine {
	namespace resource_manager {
		ResourceManager3D::ResourceManager3D(std::string base_path_)
		{
			this->base_path_ = base_path_;
		}
		ResourceManager3D::~ResourceManager3D()
		{
		}

		renderable::IRenderable3D<float*>* ResourceManager3D::LoadObj(std::string path_relative_to_base)
		{
			std::ifstream ifs(base_path_ + path_relative_to_base);
			if (!ifs.is_open()) {
				std::cout << "Failed to open file " + path_relative_to_base;
			}
			std::string line;
			std::string fileString;

			while (std::getline(ifs, line)) {
				std::cout << line << std::endl;
				fileString += line;
			}
			return nullptr;
		}
	}
}
