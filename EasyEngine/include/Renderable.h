#pragma once

#include <string>

#ifndef RENDERABLE_H
namespace easy_engine {
	namespace renderable {
		class Renderable {
			public:
				std::string name;
				virtual ~Renderable() {};
		};
	}
}
#endif // !RENDERABLE_H