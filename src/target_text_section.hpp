#ifndef REGEX_EXPLORE_TARGET_TEXT_SECTION_HPP
#define REGEX_EXPLORE_TARGET_TEXT_SECTION_HPP
#include <fstream>
#include <iterator>
#include <string>
#include <utility>

#include <cppurses/widget/layouts/vertical.hpp>
#include <cppurses/widget/pipe.hpp>
#include <cppurses/widget/widgets/open_file.hpp>

#include "textbox_highlight.hpp"

namespace regex_explore {

class Target_text_section : public cppurses::layout::Vertical<> {
   public:
    Highlight_and_scroll& highlight_and_scroll =
        make_child<Highlight_and_scroll>();
    cppurses::Open_file<>& open_file = make_child<cppurses::Open_file<>>();

   public:
    Target_text_section()
    {
        open_file.open_requested.connect([this](std::ifstream& ifs) {
            auto contents = std::string{std::istreambuf_iterator<char>(ifs),
                                        std::istreambuf_iterator<char>()};
            highlight_and_scroll.tb_highlight.set_contents(std::move(contents));
        });

        using namespace cppurses::pipe;
        using cppurses::Color;

        open_file.filename_edit | bg(Color::Black) | fg(Color::White) |
            ghost(Color::Light_gray);
    }
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_TARGET_TEXT_SECTION_HPP
