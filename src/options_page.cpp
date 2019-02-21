#include "options_page.hpp"

#include <cppurses/painter/color.hpp>

using namespace cppurses;

namespace regex_explore {

Options_page::Options_page() {
    options_box.height_policy.fixed(5);
    change_page.height_policy.fixed(1);
    change_page.brush.set_background(Color::Blue);
    change_page.brush.set_foreground(Color::White);
}
}  // namespace regex_explore
