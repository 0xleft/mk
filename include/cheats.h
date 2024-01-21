#pragma once

#include <cmath>

// some nastly bypasses to get around numworks linker

namespace std {
	void __throw_out_of_range_fmt(char const*, ...) {
	}

    void __throw_length_error(char const*) {
    }

	void __throw_bad_alloc() {
		
	}
}

void operator delete(void* ptr, unsigned int size) {
	free(ptr);
}

void* operator new(size_t size) {
	return malloc(size);
}
void operator delete(void* ptr) {
	free(ptr);
}