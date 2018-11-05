#ifndef REGEX_EXPLORE_OPTIONS_PAGE_HPP
#define REGEX_EXPLORE_OPTIONS_PAGE_HPP
#include <cppurses/painter/glyph_string.hpp>
#include <cppurses/widget/layouts/vertical_layout.hpp>
#include <cppurses/widget/widget.hpp>
#include <cppurses/widget/widgets/push_button.hpp>

#include "options_box.hpp"

namespace regex_explore {

struct Options_page : cppurses::Vertical_layout {
    Options_page();

    Options_box& options_box{this->make_child<Options_box>()};
    cppurses::Widget& blank{this->make_child<cppurses::Widget>()};
    cppurses::Push_button& change_page{
        this->make_child<cppurses::Push_button>("> Reference <")};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_OPTIONS_PAGE_HPP
