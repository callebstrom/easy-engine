#include <EasyEngine/eepch.h>
#include <EasyEngine/resource_manager/ResourceManager3D.h>

#include <Eigen/Core>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

namespace easy_engine {
	namespace resource_manager {

		resource::Mesh* ResourceManager3D::LoadObj(std::string file_path) {
			resource::Mesh* renderable = new resource::Mesh();

			renderable->name = file_path;

			std::ifstream ifs(file_path);
			if (!ifs.is_open()) {
				std::cout << "Failed to open file " + file_path;
			}
			std::string line;
			std::string fileString;
			int vertex_index = 0;
			uint32_t vertex_count = 0;

			Eigen::Matrix<float, -1, 3, Eigen::RowMajor> vertices;
			std::vector<ushort_t> vertex_indices;

			while (std::getline(ifs, line)) {
				std::stringstream string_stream_outer(line.c_str());

				std::string first_char, second_char;
				string_stream_outer >> first_char >> second_char;

				// If obj vertex annotation
				if (strcmp(first_char.c_str(), "v") == 0 && strcmp(second_char.c_str(), " ")) {
					vertex_count++;
					__int64 current_index = vertices.rows();
					std::stringstream string_stream_inner(line.c_str());
					std::string v, x, y, z;

					string_stream_inner >> v >> x >> y >> z;

					Eigen::Vector3f vec;

					vec << (float)std::atof(x.c_str()), (float)std::atof(y.c_str()), (float)std::atof(z.c_str());

					vertices.conservativeResize(vertices.rows() + 1, Eigen::NoChange);
					vertices.row(vertices.rows() - 1) = vec;
				}
				else if (strcmp(first_char.c_str(), "f") == 0) {
					std::string line_trimmed = line.substr(2);// "1/3/4 3/4/3"

					std::vector<std::string> face_coords;
					boost::split(face_coords, line_trimmed, boost::is_any_of(" ")); // ["1/3/4","3/4/3",...]

					for (auto const& fc : face_coords) { // Index
						std::vector<std::string> face_coords_exploded;
						boost::split(face_coords_exploded, fc, boost::is_any_of("/")); // ["1","3","4"]
						vertex_indices.push_back(boost::lexical_cast<ushort_t>(face_coords_exploded.at(0)) - 1);  // OBJ index starts at 1
					}
				}
			}

			renderable->SetVertices(vertices);
			renderable->SetVertexIndices(vertex_indices);
			renderable->SetVertexCount(vertex_count);

			return renderable;
		}
	}
}
