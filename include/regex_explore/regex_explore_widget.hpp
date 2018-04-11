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

   private:
    Top_bar& top_bar_{this->make_child<Top_bar>()};

    Target_text_section& target_text_section_{
        this->make_child<Target_text_section>()};

    Bottom_bar& bottom_bar_{this->make_child<Bottom_bar>(
        &target_text_section_.highlight_and_scroll.tb_highlight)};

    Regex_store regex_store_;

    void clear_displays();
    void update_displays();

    // void perform_search_and_update();
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
