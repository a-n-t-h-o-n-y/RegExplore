#ifndef REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
#define REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
#include <cstddef>
#include <regex>
#include <string>

#include <cppurses/widget/layouts/vertical.hpp>

#include "bottom_bar.hpp"
#include "regex_engine.hpp"
#include "target_text_section.hpp"
#include "top_bar.hpp"

namespace regex_explore {

class Regex_explore_widget : public cppurses::layout::Vertical<> {
   public:
    Regex_explore_widget();

   public:
    Top_bar& top_bar = make_child<Top_bar>();
    Target_text_section& target_text_section =
        make_child<Target_text_section>();
    Bottom_bar& bottom_bar = make_child<Bottom_bar>();

   private:
    Regex_engine regex_engine_;

   private:
    void clear_displays();

    void update_displays();

    // Connected to Signals
    void set_target_text(std::string const& text);

    void set_regex_text(std::string const& regex);

    void set_regex_type(std::string const& option);

    void add_option(std::regex::flag_type option);

    void remove_option(std::regex::flag_type option);

    void set_matchbox_text(std::size_t text_index);
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
