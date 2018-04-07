#ifndef REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
#define REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
#include <cppurses/widget/layouts/vertical_layout.hpp>

#include <regex_explore/textbox_highlight.hpp>
#include <regex_explore/top_bar.hpp>

namespace regex_explore {

class Regex_explore_widget : public cppurses::Vertical_layout {
   public:
   private:
    Top_bar& top_bar_{this->make_child<Top_bar>()};
    Textbox_highlight& tb_highlight{this->make_child<Textbox_highlight>()};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
