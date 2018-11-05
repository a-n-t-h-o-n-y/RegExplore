#ifndef REGEX_EXPLORE_MATCH_BOX_HPP
#define REGEX_EXPLORE_MATCH_BOX_HPP
#include <string>
#include <vector>

#include <cppurses/widget/widgets/textbox.hpp>

namespace regex_explore {

struct Match_box : public cppurses::Textbox {
    void display_match(const std::vector<std::string> match_strings);
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_MATCH_BOX_HPP
