#ifndef REGEX_EXPLORE_BOTTOM_BAR_HPP
#define REGEX_EXPLORE_BOTTOM_BAR_HPP
#include <cppurses/widget/layouts/horizontal_layout.hpp>

#include <regex_explore/match_box.hpp>
#include <regex_explore/match_page.hpp>
#include <regex_explore/options_and_reference.hpp>

namespace regex_explore {

struct Bottom_bar : cppurses::Horizontal_layout {
    Match_page& match_page{this->make_child<Match_page>()};
    Options_and_reference& options_and_reference{
        this->make_child<Options_and_reference>()};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_BOTTOM_BAR_HPP
