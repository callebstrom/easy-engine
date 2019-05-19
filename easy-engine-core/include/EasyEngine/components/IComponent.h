#ifndef I_COMPONENT_H
#define I_COMPONENT_H
#pragma once

#include <EasyEngine/Common.h>

namespace easy_engine {
	namespace component {

		struct EASY_ENGINE_API ComponentCounter {
			static int familyCounter;
		};

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

		template <typename ComponentType, typename std::enable_if<std::is_base_of<IComponent, ComponentType>::value>::type* = nullptr>
		static int GetComponentFamily() {
			static int family = ComponentCounter::familyCounter++;
			return family;
		}

	}
}


#endif // !I_COMPONENT_H
