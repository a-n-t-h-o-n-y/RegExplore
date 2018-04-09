#include <regex_explore/options_page.hpp>

#include <cppurses/widget/size_policy.hpp>

namespace regex_explore {

Options_page::Options_page() {
    change_page.height_policy.type(cppurses::Size_policy::Fixed);
    change_page.height_policy.hint(1);
}

}  // namespace regex_explore
