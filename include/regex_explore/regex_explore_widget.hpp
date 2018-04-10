#ifndef REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
#define REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
#include <regex>

#include <cppurses/widget/layouts/vertical_layout.hpp>

#include <regex_explore/bottom_bar.hpp>
#include <regex_explore/target_text_section.hpp>
#include <regex_explore/top_bar.hpp>

namespace regex_explore {

class Regex_explore_widget : public cppurses::Vertical_layout {
   public:
    Regex_explore_widget();

   private:
    Top_bar& top_bar_{this->make_child<Top_bar>()};

    Target_text_section& target_text_section_{
        this->make_child<Target_text_section>()};

    Bottom_bar& bottom_bar_{this->make_child<Bottom_bar>(
        &target_text_section_.highlight_and_scroll.tb_highlight)};

    void perform_search_and_update();

    void unset_option(std::regex::flag_type option);
    void set_option(std::regex::flag_type option);

    // Regex Parameters
    std::regex::flag_type regex_type_{std::regex::ECMAScript};
    std::regex::flag_type regex_options_{static_cast<std::regex::flag_type>(0)};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
