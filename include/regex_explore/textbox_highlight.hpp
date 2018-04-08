#ifndef REGEX_EXPLORER_TEXTBOX_HIGHLIGHT_HPP
#define REGEX_EXPLORER_TEXTBOX_HIGHLIGHT_HPP
#include <cstddef>
#include <vector>

#include <cppurses/painter/color.hpp>
#include <cppurses/widget/widgets/textbox.hpp>

namespace regex_explore {

struct Range {
    std::size_t index;
    std::size_t length;
}

class Textbox_highlight : public cppurses::Textbox {
   public:
    Textbox_highlight();

    void set_highlight(cppurses::Color color);

    void add_range(const Range& range);
    void clear_ranges();
    void remove_range(std::size_t index);

    bool paint_event() override;

   private:
    std::vector<Range> highlight_ranges_;
    cppurses::Color highlight_color_;

    add_highlights(); // these two are used by paint_event()
    remove_highlights();
};

// main widget will connection the text_changed signal from this guy^ to a
// function that (1) calculates the new search results from the regex.
// (2) calls clear_ranges() on this guy and then adds each range in
// from the results that it finds from the regex.

}  // namespace regex_explore
#endif  // REGEX_EXPLORER_TEXTBOX_HIGHLIGHT_HPP
