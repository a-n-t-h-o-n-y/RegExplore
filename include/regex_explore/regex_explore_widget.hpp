#ifndef REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
#define REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
#include <regex>

#include <cppurses/widget/layouts/vertical_layout.hpp>

#include <regex_explore/bottom_bar.hpp>
#include <regex_explore/textbox_highlight.hpp>
#include <regex_explore/top_bar.hpp>

namespace regex_explore {

class Regex_explore_widget : public cppurses::Vertical_layout {
   public:
    Regex_explore_widget();

    // single function that calculates regext search from current contents and
    // current regex, sends indicies to highlight box

   private:
    // regex_line_ changes regex_ expression and recompiles it.
    // regex_type_select_ changes the type of regex_
    Top_bar& top_bar_{this->make_child<Top_bar>()};

    // provides a slot to call each time something in top bar is changed, and a
    // signal for text change that should search the text again and rehighlight
    Textbox_highlight& tb_highlight_{this->make_child<Textbox_highlight>()};

    Bottom_bar& bottom_bar_{this->make_child<Bottom_bar>()};

    std::regex regex_;

    // change these sigs to use private vars you already have.
    sig::Slot<void(const cppurses::Glyph_string&)> update_highlights_slot(
        Textbox_highlight& box);
    void update_highlights(Textbox_highlight& box, const std::string& text);
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_REGEX_EXPLORE_WIDGET_HPP
