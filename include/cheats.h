#pragma once

#include <cmath>
#include <string>

// nasty hacks to get around fucking linkers cuz embedded systems

namespace std {
	void __throw_out_of_range_fmt(char const*, ...) {
	}

    void __throw_length_error(char const*) {
    }
}

//ez cheat but still probably bad cuz we have like no memory
void* operator new(size_t size) {
	return malloc(size);
}
void operator delete(void* ptr) {
	free(ptr);
}