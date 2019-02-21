#include "top_bar.hpp"

#include <cppurses/painter/color.hpp>

using namespace cppurses;

namespace regex_explore {

Regex_enter::Regex_enter() {
    label.width_policy.fixed(7);
    regex_edit.set_ghost_color(Color::Light_gray);
}

Top_bar::Top_bar() {
    this->height_policy.fixed(1);
    regex_type_select.width_policy.maximum(18);
    regex_type_select.set_divider(L'▸');

    auto& cycle_box = regex_type_select.cycle_box;
    cycle_box.add_option("ECMAScript");
    cycle_box.add_option("basic");
    cycle_box.add_option("extended");
    cycle_box.add_option("awk");
    cycle_box.add_option("grep");
    cycle_box.add_option("egrep");
}
}  // namespace regex_explore
