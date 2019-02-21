#include "options_box.hpp"

#include <regex>

#include <cppurses/painter/color.hpp>

using namespace cppurses;

namespace regex_explore {

Options_box::Options_box() {
    label.brush.set_background(Color::Light_gray);
    label.brush.set_foreground(Color::Black);
    label.set_alignment(Alignment::Center);

    case_insensitive.checked.connect(
        [this] { this->option_enabled(std::regex::icase); });
    case_insensitive.unchecked.connect(
        [this] { this->option_disabled(std::regex::icase); });
    no_subexpressions.checked.connect(
        [this] { this->option_enabled(std::regex::nosubs); });
    no_subexpressions.unchecked.connect(
        [this] { this->option_disabled(std::regex::nosubs); });
    optimize.checked.connect(
        [this] { this->option_enabled(std::regex::optimize); });
    optimize.unchecked.connect(
        [this] { this->option_disabled(std::regex::optimize); });
    collate.checked.connect(
        [this] { this->option_enabled(std::regex::collate); });
    collate.unchecked.connect(
        [this] { this->option_disabled(std::regex::collate); });
}
}  // namespace regex_explore
