#ifndef REGEX_EXPLORE_BOTTOM_BAR_HPP
#define REGEX_EXPLORE_BOTTOM_BAR_HPP
#include <cppurses/widget/layouts/horizontal.hpp>
#include <cppurses/widget/pipe.hpp>

#include "match_box.hpp"
#include "match_page.hpp"
#include "options_and_reference.hpp"

namespace regex_explore {

class Bottom_bar : public cppurses::layout::Horizontal<> {
   public:
    Bottom_bar() { *this | cppurses::pipe::fixed_height(6); }

   public:
    Match_page& match_page = make_child<Match_page>();
    Options_and_reference& options_and_reference =
        make_child<Options_and_reference>();
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_BOTTOM_BAR_HPP
