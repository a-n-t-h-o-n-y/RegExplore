#ifndef REGEX_EXPLORE_TOP_BAR_HPP
#define REGEX_EXPLORE_TOP_BAR_HPP
#include <cppurses/widget/layouts/horizontal_layout.hpp>
#include <cppurses/widget/widgets/label.hpp>
#include <cppurses/widget/widgets/labeled_cycle_box.hpp>
#include <cppurses/widget/widgets/line_edit.hpp>

namespace regex_explore {

struct Regex_enter : cppurses::Horizontal_layout {
    Regex_enter();

    cppurses::Label& label{this->make_child<cppurses::Label>("Regex:")};
    cppurses::Line_edit& regex_edit{
        this->make_child<cppurses::Line_edit>(R"(r(eg)e[x])")};
};

struct Top_bar : cppurses::Horizontal_layout {
    Top_bar();

    Regex_enter& regex_enter{this->make_child<Regex_enter>()};
    cppurses::Labeled_cycle_box& regex_type_select{
        this->make_child<cppurses::Labeled_cycle_box>("Type")};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_TOP_BAR_HPP
