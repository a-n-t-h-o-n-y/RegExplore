#ifndef REGEX_EXPLORE_OPTIONS_BOX_HPP
#define REGEX_EXPLORE_OPTIONS_BOX_HPP
#include <cppurses/widget/layouts/vertical_layout.hpp>
#include <cppurses/widget/widgets/checkbox.hpp>
#include <cppurses/widget/widgets/label.hpp>
#include <signals/signal.hpp>

#include <regex_explore/option_flag.hpp>

namespace regex_explore {

struct Options_box : cppurses::Vertical_layout {
    Options_box();
    using Checkbox = cppurses::Checkbox;

    cppurses::Label& label{this->make_child<cppurses::Label>("RegEx Options")};
    Checkbox& case_insensitive{this->make_child<Checkbox>("Case Insensitive")};
    Checkbox& no_subexpressions{make_child<Checkbox>("No Subexpressions")};
    Checkbox& optimize{this->make_child<Checkbox>("Optimize")};
    Checkbox& collate{this->make_child<Checkbox>("Collate(locale)")};

    sig::Signal<void(Option_flag)> option_enabled;
    sig::Signal<void(Option_flag)> option_disabled;
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_OPTIONS_BOX_HPP
