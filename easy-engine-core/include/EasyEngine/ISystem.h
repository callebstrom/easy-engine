#ifndef I_SYSTEM_H
#define I_SYSTEM_H
#pragma once

namespace easy_engine {
	class ISystem {
	public:
		virtual void Update(float dt) = 0;
	};
}

#endif // !I_SYSTEM_H

