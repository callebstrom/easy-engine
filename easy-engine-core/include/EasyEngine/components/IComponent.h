#ifndef I_COMPONENT_H
#define I_COMPONENT_H
#pragma once

namespace easy_engine {
	namespace component {
		class EASY_ENGINE_API IComponent {
		public:
			IComponent() = default;
			virtual ~IComponent() = default;
			IComponent(const IComponent&) = default;
			IComponent& operator=(const IComponent&) = default;
			IComponent(IComponent&&) = default;
			IComponent& operator=(IComponent&&) = default;

			float id;
		};
	}
}


#endif // !I_COMPONENT_H
