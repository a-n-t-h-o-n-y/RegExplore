#ifndef REGEX_EXPLORE_TARGET_TEXT_SECTION_HPP
#define REGEX_EXPLORE_TARGET_TEXT_SECTION_HPP
#include <cppurses/widget/layouts/vertical_layout.hpp>
#include <cppurses/widget/widgets/open_file.hpp>

#include <regex_explore/textbox_highlight.hpp>

namespace regex_explore {

struct Target_text_section : cppurses::Vertical_layout {
    Target_text_section();
    Textbox_highlight& tb_highlight{this->make_child<Textbox_highlight>()};
    cppurses::Open_file<>& open_file{this->make_child<cppurses::Open_file<>>()};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_TARGET_TEXT_SECTION_HPP
