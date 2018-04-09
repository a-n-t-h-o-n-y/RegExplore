#include <regex_explore/bottom_bar.hpp>

#include <regex_explore/options_page.hpp>
#include <regex_explore/reference_page.hpp>

namespace regex_explore {

Bottom_bar::Bottom_bar(const Textbox_highlight* highlight_box)
    : submatch_display{this->make_child<Submatch_display>(highlight_box)} {
}

}  // namespace regex_explore
