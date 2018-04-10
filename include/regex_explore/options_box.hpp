#ifndef REGEX_EXPLORE_OPTIONS_BOX_HPP
#define REGEX_EXPLORE_OPTIONS_BOX_HPP
#include <cppurses/widget/layouts/vertical_layout.hpp>
#include <cppurses/widget/widgets/checkbox.hpp>
#include <cppurses/widget/widgets/label.hpp>

namespace regex_explore {

struct Options_box : cppurses::Vertical_layout {
    Options_box();

    cppurses::Label& label{this->make_child<cppurses::Label>("RegEx Options")};
    cppurses::Checkbox& case_insensitive{
        this->make_child<cppurses::Checkbox>("Case Insensitive")};
    cppurses::Checkbox& no_subexpressions{
        this->make_child<cppurses::Checkbox>("No Subexpressions")};
    cppurses::Checkbox& optimize{
        this->make_child<cppurses::Checkbox>("Optimize")};
    cppurses::Checkbox& collate{
        this->make_child<cppurses::Checkbox>("Collate(locale)")};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_OPTIONS_BOX_HPP
