#ifndef REGEX_EXPLORE_OPTIONS_AND_REFERENCE_HPP
#define REGEX_EXPLORE_OPTIONS_AND_REFERENCE_HPP
#include <cppurses/widget/layouts/stack.hpp>

#include "options_page.hpp"
#include "reference_page.hpp"

namespace regex_explore {

struct Options_and_reference : cppurses::layout::Stack {
    Options_and_reference();

    Options_page& options_page{this->make_page<Options_page>()};
    Reference_page& reference_page{this->make_page<Reference_page>()};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_OPTIONS_AND_REFERENCE_HPP
