#include <regex_explore/bottom_bar.hpp>

namespace regex_explore {

Bottom_bar::Bottom_bar() {
    cppurses::enable_border(submatch_display);
    cppurses::enable_border(options_box);
}

}  // namespace regex_explore
