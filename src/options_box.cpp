#include <regex_explore/options_box.hpp>

#include <cppurses/painter/color.hpp>

namespace regex_explore {

Options_box::Options_box() {
    cppurses::set_background(label, cppurses::Color::Light_gray);
    cppurses::set_foreground(label, cppurses::Color::Black);

    label.set_alignment(cppurses::Alignment::Center);

    case_insensitive.checked.connect(
        [this] { this->option_enabled(Option_flag::case_insensitive); });
    case_insensitive.unchecked.connect(
        [this] { this->option_disabled(Option_flag::case_insensitive); });

    no_subexpressions.checked.connect(
        [this] { this->option_enabled(Option_flag::no_subexpressions); });
    no_subexpressions.unchecked.connect(
        [this] { this->option_disabled(Option_flag::no_subexpressions); });

    optimize.checked.connect(
        [this] { this->option_enabled(Option_flag::optimize); });
    optimize.unchecked.connect(
        [this] { this->option_disabled(Option_flag::optimize); });

    collate.checked.connect(
        [this] { this->option_enabled(Option_flag::collate); });
    collate.unchecked.connect(
        [this] { this->option_disabled(Option_flag::collate); });
}

}  // namespace regex_explore
