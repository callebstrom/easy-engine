#pragma once

namespace easy_engine {
	namespace lifecycle {
		class IOnInit {
		public:
			virtual void OnInit() = 0;
		};
	}
}
