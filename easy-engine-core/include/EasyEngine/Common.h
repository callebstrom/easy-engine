#ifndef COMMON_H
#define COMMON_H
#pragma once

#include <EasyEngine/ecs/component/Component.h>

template<typename OrderedDataType>
using OrderedTypeMap = std::map<std::type_index, OrderedDataType>;

using ComponentSignature = std::bitset<2048>;

struct ComponentSignatureComparetor
{
	bool operator() (const ComponentSignature& left, const ComponentSignature& right) const
	{
		for (unsigned int i = 0; i < left.size(); i++) {
			if (left.test(i)) {
				if (!right.test(i)) return false;
			}
			else {
				if (right.test(i)) return true;
			}
			return false;
		}
	}
};

#endif // !COMMON_H

