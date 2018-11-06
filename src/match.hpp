#ifndef REGEX_EXPLORE_MATCH_HPP
#define REGEX_EXPLORE_MATCH_HPP
#include <vector>

#include "range.hpp"

namespace regex_explore {

struct Match {
    Range full;
    std::vector<Range> submatches;
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_MATCH_HPP
