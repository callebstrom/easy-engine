#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H
#pragma once

#ifdef DLLDIR_EX
#include <EasyEngine/Logger.h>
#endif

namespace easy_engine {
	namespace memory {

		template <typename T>
		class LinearAllocator
		{

		public:
			LinearAllocator(size_t initial_size = 4)
				: buffer_size_(initial_size)
				, offset_(0)
				, buffer(reinterpret_cast<T*>(malloc((sizeof* this->buffer)* initial_size)))
			{}

			size_t Allocate(Ref<T> t)
			{
				if (this->offset_ == this->buffer_size_)
					this->Reallocate();

				memcpy(this->buffer + this->offset_, t.get(), sizeof * this->buffer);
				return this->offset_++;
			}

			void Reallocate()
			{
				this->buffer_size_ *= 2;
				this->buffer = reinterpret_cast<T*>(realloc(this->buffer, (sizeof * this->buffer) * this->buffer_size_));
			}
			T* buffer;
		private:
			size_t buffer_size_;
			size_t offset_;
		};
	}
}

#endif // !LINEAR_ALLOCATOR_H