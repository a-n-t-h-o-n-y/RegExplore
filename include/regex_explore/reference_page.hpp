#ifndef REGEX_EXPLORE_REFERENCE_PAGE_HPP
#define REGEX_EXPLORE_REFERENCE_PAGE_HPP
#include <cppurses/widget/layouts/vertical_layout.hpp>
#include <cppurses/widget/widgets/push_button.hpp>
#include <cppurses/widget/widgets/textbox.hpp>

#include <regex_explore/options_box.hpp>

namespace regex_explore {

struct Reference_page : cppurses::Vertical_layout {
    Reference_page();

    cppurses::Textbox& reference_box{this->make_child<cppurses::Textbox>()};
    cppurses::Push_button& change_page{
        this->make_child<cppurses::Push_button>("Options")};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_REFERENCE_PAGE_HPP
