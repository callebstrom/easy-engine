#ifndef CONFIGURATION
#define CONFIGURATION
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
			inline V Get(K key) {
				return this->configuration_map_[key];
			}

			inline void Set(K key, V val) {
				configuration_map_[key] = val;
			}
		};
	}
}
#endif // !CONFIGURATION
