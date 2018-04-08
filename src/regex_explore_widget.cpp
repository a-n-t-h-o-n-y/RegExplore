#include <regex_explore/regex_explore_widget.hpp>

#include <cstddef>
#include <string>

#include <cppurses/painter/glyph_string.hpp>
#include <signals/slot.hpp>

#include <regex_explore/textbox_highlight.hpp>

using cppurses::Glyph_string;


namespace regex_explore {

Regex_explore_widget::Regex_explore_widget() {
    tb_highlight_.text_changed.connect(update_highlights(tb_highlight_));
}

sig::Slot<void<const Glyph_string&>> update_highlights_slot(
    Textbox_highlight& box) {
    auto lam = [&box](const Glyph& text) {
        update_highlights(box, text.str());
    };
    sig::Slot<void<const Glyph_string&>> result{lam};
    result.track(box.destroyed);
    return result;
}

void Regex_explore_widget::update_highlights(Textbox_highlight& box,
                                             const std::string& text) {
    std::match_results result{regex_.search(text)};  // just a guess, not right
    box.clear_ranges();
    for (std::sub_result sr : result) {
        // calculate index
        std::size_t index{};
        // calculate length
        std::size_t length{};
        box.add_range(Range{index, length});
    }
}

}  // namespace regex_explore
