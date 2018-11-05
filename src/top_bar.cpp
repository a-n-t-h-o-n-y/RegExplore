#include "top_bar.hpp"

#include <cppurses/painter/color.hpp>
#include <cppurses/widget/size_policy.hpp>

namespace regex_explore {

Regex_enter::Regex_enter() {
    label.width_policy.type(cppurses::Size_policy::Fixed);
    label.width_policy.hint(7);

    regex_edit.set_ghost_color(cppurses::Color::Light_gray);
}

Top_bar::Top_bar() {
    this->height_policy.type(cppurses::Size_policy::Fixed);
    this->height_policy.hint(1);

    regex_type_select.width_policy.type(cppurses::Size_policy::Maximum);
    regex_type_select.width_policy.hint(18);
    regex_type_select.set_divider(L'▸');

    regex_type_select.cycle_box.add_option("ECMAScript");
    regex_type_select.cycle_box.add_option("basic");
    regex_type_select.cycle_box.add_option("extended");
    regex_type_select.cycle_box.add_option("awk");
    regex_type_select.cycle_box.add_option("grep");
    regex_type_select.cycle_box.add_option("egrep");
}

}  // namespace regex_explore
