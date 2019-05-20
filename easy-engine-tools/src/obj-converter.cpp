#include <obj-converter.h>

using easy_engine::resource_manager::ResourceManager3D;
using easy_engine::resource::Mesh;


void ConvertObjFile(std::string file_path) {
	ResourceManager3D* render_manager = new ResourceManager3D();
	Mesh* renderable = render_manager->LoadObj(file_path);

	std::ofstream ofs("C:\\test\\test.renderable");
	{
		boost::archive::text_oarchive oa(ofs);
		oa << renderable;
	}
}