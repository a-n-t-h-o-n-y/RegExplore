#include <regex_explore/regex_explore_widget.hpp>

#include <cstddef>
#include <regex>
#include <string>

#include <cppurses/painter/glyph_string.hpp>
#include <signals/slot.hpp>

#include <regex_explore/match.hpp>
#include <regex_explore/textbox_highlight.hpp>

using cppurses::Glyph_string;

namespace regex_explore {

Regex_explore_widget::Regex_explore_widget() {
    target_text_section_.tb_highlight.text_changed.connect(
        [this](const auto&) { this->perform_search_and_update(); });
    top_bar_.regex_enter.regex_edit.text_changed.connect(
        [this](const auto&) { this->perform_search_and_update(); });

    target_text_section_.height_policy.stretch(3);
}

// Attach this as a slot to all signals that signal a change to the system from
// the UI
void Regex_explore_widget::perform_search_and_update() {
    // Get regex text
    std::string regex_str{top_bar_.regex_enter.regex_edit.contents().str()};
    if (regex_str.empty()) {
        target_text_section_.tb_highlight.clear_all_highlights();
        return;
    }

    // Get regex options

    // Get regex Type

    // Create Regex object with above parameters
    std::regex regex;
    try {
        regex.assign(regex_str);
    } catch (const std::regex_error& re) {
        // info box to show invalid regex would be helpful
    }

    // Get target text
    std::string target_text{target_text_section_.tb_highlight.contents().str()};

    // Clear the current tb_highlight of ranges.
    target_text_section_.tb_highlight.clear_all_highlights();
    bottom_bar_.submatch_display.clear_all_matches();

    // Search target text with above regex in a loop
    for (std::sregex_iterator i{std::sregex_iterator(
             std::begin(target_text), std::end(target_text), regex)};
         i != std::sregex_iterator(); ++i) {
        std::smatch match{*i};
        // Entire Match
        Range range_entire{static_cast<std::size_t>(match.position(0)),
                           static_cast<std::size_t>(match.length(0))};
        target_text_section_.tb_highlight.add_highlight(range_entire);

        // Submatches
        Match match_data{range_entire};
        for (std::size_t i{1}; i < match.size(); ++i) {
            Range sub_range{static_cast<std::size_t>(match.position(i)),
                            static_cast<std::size_t>(match.length(i))};
            match_data.submatches.push_back(sub_range);
        }
    }
}

sig::Slot<void(const Glyph_string&)> update_highlights_slot(
    Textbox_highlight& box) {
    auto lam = [&box](const cppurses::Glyph_string& text) {
        // update_highlights(box, text.str());
    };
    sig::Slot<void(const Glyph_string&)> result{lam};
    result.track(box.destroyed);
    return result;
}

void Regex_explore_widget::update_highlights(Textbox_highlight& box,
                                             const std::string& text) {
    // std::match_results result{regex_.search(text)};  // just a guess, not
    // right box.clear_ranges(); for (std::sub_result sr : result) {
    //     // calculate index
    //     std::size_t index{};
    //     // calculate length
    //     std::size_t length{};
    //     box.add_range(Range{index, length});
    // }
}

}  // namespace regex_explore
