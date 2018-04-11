#include <regex_explore/bottom_bar.hpp>

#include <regex_explore/match_page.hpp>
#include <regex_explore/textbox_highlight.hpp>

namespace regex_explore {

Bottom_bar::Bottom_bar(const Textbox_highlight* highlight_box)
    : match_page{this->make_child<Match_page>(highlight_box)} {}

}  // namespace regex_explore
