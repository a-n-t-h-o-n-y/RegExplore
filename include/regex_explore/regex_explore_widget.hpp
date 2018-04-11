#ifndef REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
#define REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
#include <cppurses/widget/layouts/vertical_layout.hpp>

#include <regex_explore/bottom_bar.hpp>
#include <regex_explore/regex_store.hpp>
#include <regex_explore/target_text_section.hpp>
#include <regex_explore/top_bar.hpp>

namespace regex_explore {

class Regex_explore_widget : public cppurses::Vertical_layout {
   public:
    Regex_explore_widget();

    Top_bar& top_bar{this->make_child<Top_bar>()};
    Target_text_section& target_text_section{
        this->make_child<Target_text_section>()};
    Bottom_bar& bottom_bar{this->make_child<Bottom_bar>()};

   private:
    Regex_store regex_store_;

    void clear_displays();
    void update_displays();

    // Connected to Signals
    void set_target_text(const std::string& text);
    void set_regex_text(const std::string& regex);
    void set_regex_type(const std::string& option);
    void add_option(Option_flag option);
    void remove_option(Option_flag option);
    void set_matchbox_text(std::size_t text_index);
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
