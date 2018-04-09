#ifndef REGEX_EXPLORER_TEXTBOX_HIGHLIGHT_HPP
#define REGEX_EXPLORER_TEXTBOX_HIGHLIGHT_HPP
#include <cstdint>

#include <cppurses/painter/color.hpp>
#include <cppurses/widget/widgets/textbox.hpp>
#include <signals/signals.hpp>

#include <regex_explore/range.hpp>

namespace regex_explore {

class Textbox_highlight : public cppurses::Textbox {
   public:
    Textbox_highlight();

    void set_highlight(cppurses::Color color);

    void add_highlight(const Range& range);
    void remove_highlight(const Range& range);
    void clear_all_highlights();

    bool mouse_press_event(cppurses::Mouse_button button,
                           cppurses::Point global,
                           cppurses::Point local,
                           std::uint8_t device_id) override;

    sig::Signal<void(std::size_t)> clicked_at_index;

   private:
    cppurses::Color highlight_color_{cppurses::Color::Yellow};

    void add_highlights();  // these two are used by paint_event()
    void remove_highlights();
};

// main widget will connection the text_changed signal from this guy^ to a
// function that (1) calculates the new search results from the regex.
// (2) calls clear_ranges() on this guy and then adds each range in
// from the results that it finds from the regex.

}  // namespace regex_explore
#endif  // REGEX_EXPLORER_TEXTBOX_HIGHLIGHT_HPP
