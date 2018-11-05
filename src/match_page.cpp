#include "match_page.hpp"

#include <cstddef>
#include <sstream>

#include <cppurses/widget/border.hpp>
#include <cppurses/widget/widget_free_functions.hpp>

#include "match_box.hpp"

namespace regex_explore {

Match_page::Match_page() {
    disable_corners(this->border);
    disable_walls(this->border);
    this->border.east_enabled = true;
    enable_border(*this);

    set_background(label, cppurses::Color::Light_gray);
    set_foreground(label, cppurses::Color::Black);
    label.set_alignment(cppurses::Alignment::Center);
}

void Match_page::set_match_count(std::size_t count) {
    std::stringstream ss;
    ss << "Matches(" << count << ")";
    label.set_text(ss.str());
}

}  // namespace regex_explore
