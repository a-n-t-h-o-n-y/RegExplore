#ifndef REGEX_EXPLORER_TEXTBOX_HIGHLIGHT_HPP
#define REGEX_EXPLORER_TEXTBOX_HIGHLIGHT_HPP
#include <cstddef>
#include <cstdint>

#include <cppurses/painter/color.hpp>
#include <cppurses/system/mouse_button.hpp>
#include <cppurses/system/mouse_data.hpp>
#include <cppurses/widget/layouts/horizontal_layout.hpp>
#include <cppurses/widget/point.hpp>
#include <cppurses/widget/widgets/textbox.hpp>
#include <cppurses/widget/widgets/vertical_scrollbar.hpp>
#include <signals/signals.hpp>

#include "range.hpp"

namespace regex_explore {

class Textbox_highlight : public cppurses::Textbox {
   public:
    Textbox_highlight();

    void set_highlight_color(cppurses::Color color);

    void add_highlight(const Range& range);
    void remove_highlight(const Range& range);
    void clear_all_highlights();

    bool mouse_press_event(const cppurses::Mouse_data& mouse) override;

    sig::Signal<void(std::size_t)> clicked_at_index;

   private:
    cppurses::Color highlight_color_{cppurses::Color::Yellow};
};

struct Highlight_and_scroll : cppurses::Horizontal_layout {
    Textbox_highlight& tb_highlight{this->make_child<Textbox_highlight>()};
    cppurses::Vertical_scrollbar& scrollbar{
        this->make_child<cppurses::Vertical_scrollbar>(tb_highlight)};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORER_TEXTBOX_HIGHLIGHT_HPP