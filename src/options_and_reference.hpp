#ifndef REGEX_EXPLORE_OPTIONS_AND_REFERENCE_HPP
#define REGEX_EXPLORE_OPTIONS_AND_REFERENCE_HPP
#include <cppurses/widget/layouts/stack.hpp>
#include <cppurses/widget/pipe.hpp>

#include "options_page.hpp"
#include "reference_page.hpp"

namespace regex_explore {

class Options_and_reference : public cppurses::layout::Stack<> {
   public:
    Options_page& options_page     = this->make_page<Options_page>();
    Reference_page& reference_page = this->make_page<Reference_page>();

   public:
    Options_and_reference()
    {
        using namespace cppurses::pipe;

        *this | active_page(0);
        options_page.change_page | on_press([this] { *this | active_page(1); });
        reference_page.change_page |
            on_press([this] { *this | active_page(0); });
    }
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_OPTIONS_AND_REFERENCE_HPP
