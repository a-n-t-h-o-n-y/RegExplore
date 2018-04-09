#ifndef REGEX_EXPLORE_BOTTOM_BAR_HPP
#define REGEX_EXPLORE_BOTTOM_BAR_HPP
#include <cppurses/widget/layouts/horizontal_layout.hpp>
#include <cppurses/widget/widgets/text_display.hpp>

#include <regex_explore/submatch_display.hpp>

namespace regex_explore {
class Textbox_highlight;

struct Bottom_bar : cppurses::Horizontal_layout {
    Bottom_bar(const Textbox_highlight*);
    Submatch_display& submatch_display;
    cppurses::Text_display& options_box{
        this->make_child<cppurses::Text_display>("Options Box")};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_BOTTOM_BAR_HPP
