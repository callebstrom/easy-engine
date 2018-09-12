#pragma once

#include <string>

#include <Common.h>

namespace easy_engine {
	namespace renderable {
		class Renderable {
			public:
				std::string name;
				virtual ~Renderable() {};
		};
	}
}