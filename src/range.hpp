#ifndef REGEX_EXPLORE_RANGE_HPP
#define REGEX_EXPLORE_RANGE_HPP
#include <cstddef>

namespace regex_explore {

struct Range {
    std::size_t index;
    std::size_t length;
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_RANGE_HPP
