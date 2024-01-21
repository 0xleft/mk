#pragma once

#include <vector>
#include <string_view.hpp>

#include "color.hpp"
#include "coords.hpp"

namespace chess {
namespace utils {
/// @brief Split a string into a vector of strings, using a delimiter.
/// @param string
/// @param delimiter
/// @return
[[nodiscard]] static std::vector<bpstd::string_view> splitString(bpstd::string_view string, const char &delimiter) {
    std::vector<bpstd::string_view> result;
    size_t start = 0;
    size_t end   = string.find(delimiter);

    while (end != bpstd::string_view::npos) {
        result.push_back(string.substr(start, end - start));
        start = end + 1;
        end   = string.find(delimiter, start);
    }

    // Add the last chunk (or the only chunk if there are no delimiters)
    result.push_back(string.substr(start));

    return result;
}

}  // namespace utils

}  // namespace chess
