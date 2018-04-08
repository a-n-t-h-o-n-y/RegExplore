#ifndef REGEX_EXPLORER_TOP_BAR_HPP
#define REGEX_EXPLORER_TOP_BAR_HPP
#include <cppurses/widget/layouts/horizontal_layout.hpp>
#include <cppurses/widget/widgets/cycle_box.hpp>
#include <cppurses/widget/widgets/label.hpp>
#include <cppurses/widget/widgets/line_edit.hpp>

namespace regex_explore {

struct Regex_enter : cppurses::Horizontal_layout {
    Regex_enter();
    cppurses::Label& label{this->make_child<cppurses::Label>("Regex:")};
    cppurses::Line_edit& regex_edit{
        this->make_child<cppurses::Line_edit>(R"(\d\d\d)")};
};

struct Regex_type_select : cppurses::Horizontal_layout {
    Regex_type_select();
    cppurses::Label& label{this->make_child<cppurses::Label>("Type:")};
    cppurses::Cycle_box& select_box{this->make_child<cppurses::Cycle_box>()};
};

struct Top_bar : cppurses::Horizontal_layout {
    Top_bar();
    Regex_enter& regex_enter{this->make_child<Regex_enter>()};
    Regex_type_select& regex_type_select{this->make_child<Regex_type_select>()};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORER_TOP_BAR_HPP
