#include <regex_explore/match_box.hpp>

#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

namespace regex_explore {

void Match_box::display_match(const std::vector<std::string> match_strings) {
    std::stringstream ss;
    for (std::size_t i{0}; i < match_strings.size(); ++i) {
        if (i == 0) {
            ss << "Entire Match: " << match_strings[i] << '\n';
        } else {
            ss << "Group " << i << ": " << match_strings[i] << '\n';
        }
    }
    std::string result{ss.str()};
    result.pop_back();
    this->set_text(result);
}

}  // namespace regex_explore
