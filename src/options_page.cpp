#include <regex_explore/options_page.hpp>

#include <cppurses/painter/color.hpp>
#include <cppurses/widget/size_policy.hpp>

namespace regex_explore {

Options_page::Options_page() {
    options_box.height_policy.type(cppurses::Size_policy::Fixed);
    options_box.height_policy.hint(5);
    change_page.height_policy.type(cppurses::Size_policy::Fixed);
    change_page.height_policy.hint(1);

    cppurses::set_background(change_page, cppurses::Color::Blue);
    cppurses::set_foreground(change_page, cppurses::Color::White);
}

}  // namespace regex_explore
