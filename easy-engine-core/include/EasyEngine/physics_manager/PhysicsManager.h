#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H
#pragma once

namespace easy_engine {
	namespace physics_manager {

		class PhysicsManager {
		public:
			PhysicsManager();
		private:
			struct Impl;
			std::unique_ptr<Impl> p_impl_;
		};
	}
}

#endif // !PHYSICS_MANAGER_H

