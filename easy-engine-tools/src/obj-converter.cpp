#include <obj-converter.h>

using easy_engine::resource_manager::ResourceManager3D;
using easy_engine::renderable::Renderable3D;


void ConvertObjFile(std::string file_path) {
	ResourceManager3D* render_manager = new ResourceManager3D();
	Renderable3D* renderable = render_manager->LoadObj(file_path);

	std::ofstream ofs("C:\\test\\test.renderable");
	{
		boost::archive::text_oarchive oa(ofs);
		oa << renderable;
	}
}