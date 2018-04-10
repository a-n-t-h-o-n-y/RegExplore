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
            bottom_bar_.match_page.submatch_display.set_match_from_text_index(
                text_index);
        });

    target_text_section_.height_policy.stretch(3);

    // Regex Type Select
    top_bar_.regex_type_select.cycle_box.add_option("ECMAScript")
        .connect([this] {
            regex_type_ = std::regex::ECMAScript;
            this->perform_search_and_update();
        });

    top_bar_.regex_type_select.cycle_box.add_option("basic").connect([this] {
        regex_type_ = std::regex::basic;
        this->perform_search_and_update();
    });

    top_bar_.regex_type_select.cycle_box.add_option("extended").connect([this] {
        regex_type_ = std::regex::extended;
        this->perform_search_and_update();
    });

    top_bar_.regex_type_select.cycle_box.add_option("awk").connect([this] {
        regex_type_ = std::regex::awk;
        this->perform_search_and_update();
    });

    top_bar_.regex_type_select.cycle_box.add_option("grep").connect([this] {
        regex_type_ = std::regex::grep;
        this->perform_search_and_update();
    });

    top_bar_.regex_type_select.cycle_box.add_option("egrep").connect([this] {
        regex_type_ = std::regex::egrep;
        this->perform_search_and_update();
    });

    // Options Box
    auto& opt_box = bottom_bar_.options_and_reference.options_page.options_box;
    opt_box.case_insensitive.checked.connect([this] {
        this->set_option(std::regex::icase);
        this->perform_search_and_update();
    });
    opt_box.case_insensitive.unchecked.connect([this] {
        this->unset_option(std::regex::icase);
        this->perform_search_and_update();
    });

    opt_box.no_subexpressions.checked.connect([this] {
        this->set_option(std::regex::nosubs);
        this->perform_search_and_update();
    });
    opt_box.no_subexpressions.unchecked.connect([this] {
        this->unset_option(std::regex::nosubs);
        this->perform_search_and_update();
    });

    opt_box.optimize.checked.connect([this] {
        this->set_option(std::regex::optimize);
        this->perform_search_and_update();
    });
    opt_box.optimize.unchecked.connect([this] {
        this->unset_option(std::regex::optimize);
        this->perform_search_and_update();
    });

    opt_box.collate.checked.connect([this] {
        this->set_option(std::regex::collate);
        this->perform_search_and_update();
    });
    opt_box.collate.unchecked.connect([this] {
        this->unset_option(std::regex::collate);
        this->perform_search_and_update();
    });
}

// Attach this as a slot to all signals that signal a change to the system from
// the UI
void Regex_explore_widget::perform_search_and_update() {
    // Get regex text.
    std::string regex_str{top_bar_.regex_enter.regex_edit.contents().str()};

    // Create Regex object from flags.
    std::regex regex;
    top_bar_.regex_enter.regex_edit.brush.remove_background();
    this->update();
    std::regex::flag_type flags{regex_type_};
    flags |= regex_options_;
    try {
        regex.assign(regex_str, flags);
    } catch (const std::regex_error& re) {
        cppurses::set_background(top_bar_.regex_enter.regex_edit,
                                 cppurses::Color::Red);
    }

    // Get target text.
    std::string target_text{target_text_section_.tb_highlight.contents().str()};

    // Clear the current tb_highlight of ranges.
    target_text_section_.tb_highlight.clear_all_highlights();
    bottom_bar_.match_page.submatch_display.clear_all_matches();

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
        bottom_bar_.match_page.submatch_display.add_match(match_data);
    }
}

void Regex_explore_widget::unset_option(std::regex::flag_type option) {
    regex_options_ &= ~option;
}

void Regex_explore_widget::set_option(std::regex::flag_type option) {
    regex_options_ |= option;
}

}  // namespace regex_explore
