#ifndef REGEX_EXPLORE_TOP_BAR_HPP
#define REGEX_EXPLORE_TOP_BAR_HPP
#include <cppurses/widget/layouts/horizontal.hpp>
#include <cppurses/widget/pipe.hpp>
#include <cppurses/widget/widgets/cycle_box.hpp>
#include <cppurses/widget/widgets/label.hpp>
#include <cppurses/widget/widgets/line_edit.hpp>

namespace regex_explore {

class Regex_enter : public cppurses::layout::Horizontal<> {
   public:
    cppurses::HLabel& label = make_child<cppurses::HLabel>({L"Regex:"});
    cppurses::Line_edit& regex_edit =
        make_child<cppurses::Line_edit>(LR"(r(eg)e[x])");

   public:
    Regex_enter()
    {
        using namespace cppurses::pipe;
        label | fixed_width(7);
        regex_edit | ghost(cppurses::Color::Light_gray);
    }
};

class Top_bar : public cppurses::layout::Horizontal<> {
   public:
    Regex_enter& regex_enter = make_child<Regex_enter>();
    cppurses::Labeled_cycle_box& regex_type_select =
        make_child<cppurses::Labeled_cycle_box>(L"Type");

   public:
    Top_bar()
    {
        using namespace cppurses::pipe;

        *this | fixed_height(1);
        regex_type_select | maximum_width(18) | divider(L'▸');

        auto& cycle_box = regex_type_select.cycle_box;
        cycle_box.add_option(L"ECMAScript");
        cycle_box.add_option(L"basic");
        cycle_box.add_option(L"extended");
        cycle_box.add_option(L"awk");
        cycle_box.add_option(L"grep");
        cycle_box.add_option(L"egrep");
    }
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_TOP_BAR_HPP
