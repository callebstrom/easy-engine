#pragma once

#include <map>
#include <string>

namespace easy_engine {
	namespace configuration {
		template <typename K, typename V> 
		class Configuration {
			private:
				std::map<K, V> configuration_map_;

			public:
				inline V Configuration<K, V>::Get(K key) {
					return this->configuration_map_[key];
				}

				inline void Configuration<K, V>::Set(K key, V val) {
					configuration_map_[key] = val;
				}
		};
	}
}