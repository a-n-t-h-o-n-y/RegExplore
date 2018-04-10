#ifndef REGEX_EXPLORE_MATCH_PAGE_HPP
#define REGEX_EXPLORE_MATCH_PAGE_HPP
#include <cppurses/widget/layouts/vertical_layout.hpp>
#include <cppurses/widget/widgets/label.hpp>

#include <regex_explore/submatch_display.hpp>

namespace regex_explore {
class Textbox_highlight;

struct Match_page : cppurses::Vertical_layout {
    Match_page(const Textbox_highlight* highlight_box);

    cppurses::Label& label{this->make_child<cppurses::Label>("Matches")};
    Submatch_display& submatch_display;
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_MATCH_PAGE_HPP
