#ifndef HDB_ALLOC_H
#define HDB_ALLOC_H

#include <stdlib.h>

namespace hdb {

extern unsigned long allocationCount;

template <typename T>
static inline T* alloc(size_t size, size_t alignment = alignof(T)) {
	++allocationCount;
	return (T*)aligned_alloc(alignment, size * sizeof(T));
}

template <typename T>
static inline T* alloc(T*& ptr, size_t size, size_t alignment = alignof(T)) {
	++allocationCount;
	return ptr = (T*)aligned_alloc(alignment, size * sizeof(T));
}

template <typename T>
static inline void resize(T*& ptr, size_t size) {
	ptr = (T*)realloc(ptr, size * sizeof(T));
}

template <typename T>
static inline void free(T* ptr) {
	--allocationCount;
	std::free((void*)ptr);
}

template <typename T>
static inline T* allocStack(size_t size) {
	return (T*)alloca(size * sizeof(T));
}

template <typename T>
static inline T* allocStack(T*& ptr, size_t size) {
	return ptr = (T*)alloca(size * sizeof(T));
}

}

#endif
