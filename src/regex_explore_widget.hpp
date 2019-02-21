#ifndef REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
#define REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
#include <regex>

#include <cppurses/widget/layouts/vertical.hpp>

#include "bottom_bar.hpp"
#include "regex_engine.hpp"
#include "target_text_section.hpp"
#include "top_bar.hpp"

namespace regex_explore {

class Regex_explore_widget : public cppurses::layout::Vertical {
   public:
    Regex_explore_widget();

    Top_bar& top_bar{this->make_child<Top_bar>()};
    Target_text_section& target_text_section{
        this->make_child<Target_text_section>()};
    Bottom_bar& bottom_bar{this->make_child<Bottom_bar>()};

   private:
    Regex_engine regex_engine_;

    void clear_displays();
    void update_displays();

    // Connected to Signals
    void set_target_text(const std::string& text);
    void set_regex_text(const std::string& regex);
    void set_regex_type(const std::string& option);
    void add_option(std::regex::flag_type option);
    void remove_option(std::regex::flag_type option);
    void set_matchbox_text(std::size_t text_index);
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
