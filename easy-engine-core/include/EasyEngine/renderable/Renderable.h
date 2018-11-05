#ifndef RENDERABLE_H
#define RENDERABLE_H
#pragma once

#include <string>

#include <EasyEngine/Common.h>

namespace easy_engine {
	namespace renderable {
		class EASY_ENGINE_API Renderable {
			public:
				std::string name;
				virtual ~Renderable() {};
		};
	}
}

#endif // !RENDERABLE_H