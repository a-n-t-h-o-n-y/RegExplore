#include <regex_explore/top_bar.hpp>

#include <cppurses/widget/size_policy.hpp>

namespace regex_explore {

Regex_enter::Regex_enter() {
    label.width_policy.type(cppurses::Size_policy::Fixed);
    label.width_policy.hint(7);
}

Regex_type_select::Regex_type_select() {
    label.width_policy.type(cppurses::Size_policy::Fixed);
    label.width_policy.hint(6);
}

Top_bar::Top_bar() {
    this->height_policy.type(cppurses::Size_policy::Fixed);
    this->height_policy.hint(1);

    regex_type_select.width_policy.type(cppurses::Size_policy::Maximum);
    regex_type_select.width_policy.hint(17);
}

}  // namespace regex_explore
