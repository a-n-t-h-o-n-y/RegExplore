#ifndef REGEX_EXPLORER_TOP_BAR_HPP
#define REGEX_EXPLORER_TOP_BAR_HPP
#include <cppurses/widget/layouts/horizontal_layout.hpp>
#include <cppurses/widget/widgets/cycle_box.hpp>
#include <cppurses/widget/widgets/line_edit.hpp>

namespace regex_explore {

class Top_bar : public cppurses::Horizontal_layout {
   public:
    Top_bar();

   private:
    cppurses::Line_edit& regex_line_{
        this->make_child<cppurses::Line_edit>("Enter Regex Here")};
    cppurses::Cycle_box& regex_type_select_{
        this->make_child<cppurses::Cycle_box>()};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORER_TOP_BAR_HPP
