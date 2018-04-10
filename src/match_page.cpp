#include <regex_explore/match_page.hpp>

#include <sstream>

#include <cppurses/widget/border.hpp>

namespace regex_explore {

Match_page::Match_page(const Textbox_highlight* highlight_box)
    : submatch_display{this->make_child<Submatch_display>(highlight_box)} {
    cppurses::disable_corners(this->border);
    cppurses::disable_walls(this->border);
    this->border.east_enabled = true;
    cppurses::enable_border(*this);

    cppurses::set_background(label, cppurses::Color::Light_gray);
    cppurses::set_foreground(label, cppurses::Color::Black);

    label.set_alignment(cppurses::Alignment::Center);
}

void Match_page::set_match_count(std::size_t count) {
    std::stringstream ss;
    ss << "Matches(" << count << ")";
    label.set_text(ss.str());
}

}  // namespace regex_explore
