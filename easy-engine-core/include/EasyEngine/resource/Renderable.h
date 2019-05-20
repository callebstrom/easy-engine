#ifndef RENDERABLE_H
#define RENDERABLE_H
#pragma once

#include <string>

namespace easy_engine {
	namespace resource {
		class EASY_ENGINE_API Renderable {
		public:
			std::string name;
			virtual ~Renderable() {};
		};
	}
}

#endif // !RENDERABLE_H