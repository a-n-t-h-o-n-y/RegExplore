#include "match_page.hpp"

#include <cstddef>
#include <sstream>

#include <cppurses/widget/border.hpp>

#include "match_box.hpp"

using namespace cppurses;

namespace regex_explore {

Match_page::Match_page() {
    this->border.enable();
    this->border.segments.disable_all();
    this->border.segments.east.enable();
    label.brush.set_background(Color::Light_gray);
    label.brush.set_foreground(Color::Black);
    label.set_alignment(Alignment::Center);
}

void Match_page::set_match_count(std::size_t count) {
    std::stringstream ss;
    ss << "Matches(" << count << ")";
    label.set_contents(ss.str());
}

}  // namespace regex_explore
