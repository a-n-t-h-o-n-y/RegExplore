#include <regex_explore/reference_page.hpp>

#include <cppurses/widget/size_policy.hpp>

namespace regex_explore {

Reference_page::Reference_page() {
    change_page.height_policy.type(cppurses::Size_policy::Fixed);
    change_page.height_policy.hint(1);

    reference_box.disable_input();
    reference_box.set_text(R"(. 	any character except newline
\w \d \s 	word, digit, whitespace
\W \D \S 	not word, digit, whitespace
[abc] 	any of a, b, or c
[^abc] 	not a, b, or c
[a-g] 	character between a & g)");
}

}  // namespace regex_explore
