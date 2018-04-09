#include <regex_explore/regex_explore_widget.hpp>

#include <cstddef>
#include <regex>
#include <string>

#include <cppurses/painter/color.hpp>
#include <cppurses/painter/glyph_string.hpp>
#include <cppurses/widget/widget.hpp>
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

    // Submatch selection
    target_text_section_.tb_highlight.clicked_at_index.connect(
        [this](std::size_t text_index) {
            bottom_bar_.submatch_display.set_match_from_text_index(text_index);
        });

    target_text_section_.height_policy.stretch(3);

    top_bar_.regex_type_select.select_box.add_option("ECMAScript")
        .connect([this] {
            regex_type_ = std::regex::ECMAScript;
            this->perform_search_and_update();
        });

    top_bar_.regex_type_select.select_box.add_option("basic").connect([this] {
        regex_type_ = std::regex::basic;
        this->perform_search_and_update();
    });

    top_bar_.regex_type_select.select_box.add_option("extended")
        .connect([this] {
            regex_type_ = std::regex::extended;
            this->perform_search_and_update();
        });

    top_bar_.regex_type_select.select_box.add_option("awk").connect([this] {
        regex_type_ = std::regex::awk;
        this->perform_search_and_update();
    });

    top_bar_.regex_type_select.select_box.add_option("grep").connect([this] {
        regex_type_ = std::regex::grep;
        this->perform_search_and_update();
    });

    top_bar_.regex_type_select.select_box.add_option("egrep").connect([this] {
        regex_type_ = std::regex::egrep;
        this->perform_search_and_update();
    });
}

// Attach this as a slot to all signals that signal a change to the system from
// the UI
void Regex_explore_widget::perform_search_and_update() {
    // Get regex text
    std::string regex_str{top_bar_.regex_enter.regex_edit.contents().str()};

    // Get regex options

    // Create Regex object with above parameters
    std::regex regex;
    top_bar_.regex_enter.regex_edit.brush.remove_background();
    this->update();
    try {
        regex.assign(regex_str, regex_type_);
    } catch (const std::regex_error& re) {
        cppurses::set_background(top_bar_.regex_enter.regex_edit,
                                 cppurses::Color::Red);
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
        bottom_bar_.submatch_display.add_match(match_data);
    }
}

// sig::Slot<void(const Glyph_string&)> update_highlights_slot(
//     Textbox_highlight& box) {
//     auto lam = [&box](const cppurses::Glyph_string& text) {
//         // update_highlights(box, text.str());
//     };
//     sig::Slot<void(const Glyph_string&)> result{lam};
//     result.track(box.destroyed);
//     return result;
// }

// void Regex_explore_widget::update_highlights(Textbox_highlight& box,
//                                              const std::string& text) {
// std::match_results result{regex_.search(text)};  // just a guess, not
// right box.clear_ranges(); for (std::sub_result sr : result) {
//     // calculate index
//     std::size_t index{};
//     // calculate length
//     std::size_t length{};
//     box.add_range(Range{index, length});
// }
// }

}  // namespace regex_explore
