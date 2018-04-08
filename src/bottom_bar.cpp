#include <regex_explore/bottom_bar.hpp>

namespace regex_explore {

Bottom_bar::Bottom_bar() {
    cppurses::enable_border(sub_matches_);
    cppurses::enable_border(match_info_);
}

}  // namespace regex_explore
