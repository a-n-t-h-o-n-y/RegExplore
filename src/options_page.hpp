#ifndef REGEX_EXPLORE_OPTIONS_PAGE_HPP
#define REGEX_EXPLORE_OPTIONS_PAGE_HPP
#include <cppurses/painter/color.hpp>
#include <cppurses/widget/layouts/vertical.hpp>
#include <cppurses/widget/pipe.hpp>
#include <cppurses/widget/widget.hpp>
#include <cppurses/widget/widgets/button.hpp>

#include "options_box.hpp"

namespace regex_explore {

class Options_page : public cppurses::layout::Vertical<> {
   public:
    Options_box& options_box = make_child<Options_box>();
    cppurses::Widget& blank  = make_child();
    cppurses::Button& change_page =
        make_child<cppurses::Button>(L"> Reference <");

   public:
    Options_page()
    {
        using namespace cppurses::pipe;
        using cppurses::Color;
        options_box | fixed_height(5);
        change_page | fixed_height(1) | bg(Color::Blue) | fg(Color::White);
    }
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_OPTIONS_PAGE_HPP
