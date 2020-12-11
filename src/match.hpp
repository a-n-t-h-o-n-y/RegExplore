#ifndef REGEX_EXPLORE_MATCH_HPP
#define REGEX_EXPLORE_MATCH_HPP
#include <string_view>
#include <vector>

namespace regex_explore {

/// Holds string_views of the full match and sub matches.
struct Match {
    std::string_view full;
    struct Range {
        std::size_t position;
        std::size_t length;
    } range;
    std::vector<std::string_view> submatches;
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_MATCH_HPP
