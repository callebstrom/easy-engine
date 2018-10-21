#ifndef RENDERABLE_H
#define RENDERABLE_H
#pragma once

#include <string>

#include <Common.h>

namespace easy_engine {
	namespace renderable {
		class DLLEXPORT Renderable {
			public:
				std::string name;
				virtual ~Renderable() {};
		};
	}
}

#endif // !RENDERABLE_H