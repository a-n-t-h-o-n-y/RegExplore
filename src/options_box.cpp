#include <regex_explore/options_box.hpp>

#include <cppurses/painter/color.hpp>

namespace regex_explore {

Options_box::Options_box() {
    cppurses::set_background(label, cppurses::Color::Light_gray);
    cppurses::set_foreground(label, cppurses::Color::Black);

    label.set_alignment(cppurses::Alignment::Center);
}

}  // namespace regex_explore
