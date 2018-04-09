#include <regex_explore/bottom_bar.hpp>

namespace regex_explore {

Bottom_bar::Bottom_bar(const Textbox_highlight* highlight_box)
    : submatch_display{this->make_child<Submatch_display>(highlight_box)} {
    cppurses::enable_border(submatch_display);
    cppurses::enable_border(options_box);
}  // namespace regex_explore

}  // namespace regex_explore
