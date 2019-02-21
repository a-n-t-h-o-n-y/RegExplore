#ifndef REGEX_EXPLORE_TARGET_TEXT_SECTION_HPP
#define REGEX_EXPLORE_TARGET_TEXT_SECTION_HPP
#include <cppurses/widget/layouts/vertical.hpp>
#include <cppurses/widget/widgets/open_file.hpp>

#include "textbox_highlight.hpp"

namespace regex_explore {

struct Target_text_section : cppurses::layout::Vertical {
    Target_text_section();

    Highlight_and_scroll& highlight_and_scroll{
        this->make_child<Highlight_and_scroll>()};
    cppurses::Open_file<>& open_file{this->make_child<cppurses::Open_file<>>()};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_TARGET_TEXT_SECTION_HPP
