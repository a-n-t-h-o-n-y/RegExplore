#ifndef REGEX_EXPLORE_OPTIONS_BOX_HPP
#define REGEX_EXPLORE_OPTIONS_BOX_HPP
#include <regex>

#include <signals_light/signal.hpp>

#include <cppurses/painter/color.hpp>
#include <cppurses/painter/trait.hpp>
#include <cppurses/widget/layouts/vertical.hpp>
#include <cppurses/widget/pipe.hpp>
#include <cppurses/widget/widgets/checkbox.hpp>
#include <cppurses/widget/widgets/label.hpp>

namespace regex_explore {

class Option_checks
    : public cppurses::layout::Vertical<cppurses::Labeled_checkbox> {
   public:
    Option_checks()
    {
        using std::regex;
        case_insensitive.checked.connect(
            [this] { this->option_on(regex::icase); });
        case_insensitive.unchecked.connect(
            [this] { this->option_off(regex::icase); });
        no_subexpressions.checked.connect(
            [this] { this->option_on(regex::nosubs); });
        no_subexpressions.unchecked.connect(
            [this] { this->option_off(regex::nosubs); });
        optimize.checked.connect([this] { this->option_on(regex::optimize); });
        optimize.unchecked.connect(
            [this] { this->option_off(regex::optimize); });
        collate.checked.connect([this] { this->option_on(regex::collate); });
        collate.unchecked.connect([this] { this->option_off(regex::collate); });
    }

   private:
    using Checkbox = cppurses::Labeled_checkbox;

   public:
    Checkbox& case_insensitive  = make_child(L"Case Insensitive");
    Checkbox& no_subexpressions = make_child(L"No Subexpressions");
    Checkbox& optimize          = make_child(L"Optimize");
    Checkbox& collate           = make_child(L"Collate(locale)");

    sl::Signal<void(std::regex::flag_type)> option_on;
    sl::Signal<void(std::regex::flag_type)> option_off;
};

class Options_box : public cppurses::layout::Vertical<> {
   public:
    cppurses::HLabel& label = make_child<cppurses::HLabel>({"RegEx Options"});
    Option_checks& checks   = make_child<Option_checks>();

    sl::Signal<void(std::regex::flag_type)>& option_on  = checks.option_on;
    sl::Signal<void(std::regex::flag_type)>& option_off = checks.option_off;

   public:
    Options_box()
    {
        using cppurses::Color;
        using namespace cppurses::pipe;

        label | bg(Color::Light_gray) | fg(Color::Black) | align_center();
    }
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_OPTIONS_BOX_HPP
