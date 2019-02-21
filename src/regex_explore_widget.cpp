#include "regex_explore_widget.hpp"

#include <cstddef>
#include <regex>
#include <string>
#include <vector>

#include <cppurses/painter/color.hpp>
#include <cppurses/painter/glyph_string.hpp>

#include "regex_engine.hpp"

using namespace cppurses;

namespace {
using namespace regex_explore;

/// Retrieves the substring from \p text associated with \p range.
std::string extract_range(const std::string& text, const Range& range) {
    return text.substr(range.index, range.length);
}

/// Retrieves strings associated with the full and sub-matches.
std::vector<std::string> match_to_strings(const Regex_engine& engine,
                                          const Match& match) {
    std::vector<std::string> results;
    // Full Match
    results.push_back(extract_range(engine.get_target_text(), match.full));
    // Sub-Matches
    for (Range submatch : match.submatches) {
        results.push_back(extract_range(engine.get_target_text(), submatch));
    }
    return results;
}

/// Whether \p indexconversion between types is located within \p range.
bool is_within_range(std::size_t index, const Range& range) {
    return index >= range.index && index < (range.index + range.length);
}

/// Whether \p index is within the full \p match.
auto contains(std::size_t index) {
    return [index](const Match& match) {
        return is_within_range(index, match.full);
    };
}

/// Retrieves match at index within text, if there is one.
/** The first string is the full match, sub-matches follow. */
std::vector<std::string> get_match_at(const Regex_engine& engine,
                                      std::size_t text_index) {
    auto matches = engine.get_matches();
    auto find_iter = std::find_if(std::begin(matches), std::end(matches),
                                  contains(text_index));
    if (find_iter == std::end(matches)) {
        return {};
    }
    return match_to_strings(engine, *find_iter);
}
}  // namespace

namespace regex_explore {

Regex_explore_widget::Regex_explore_widget() {
    regex_engine_.set_target_text(
        target_text_section.highlight_and_scroll.tb_highlight.contents().str());
    regex_engine_.set_regex(top_bar.regex_enter.regex_edit.contents().str());

    target_text_section.height_policy.stretch(3);
    this->update_displays();

    // Change Target Text
    target_text_section.highlight_and_scroll.tb_highlight.contents_modified
        .connect([this](const Glyph_string& gs) {
            this->set_target_text(gs.str());
        });

    // Change Regex
    top_bar.regex_enter.regex_edit.contents_modified.connect(
        [this](const Glyph_string& gs) { this->set_regex_text(gs.str()); });

    // Change Regex Type
    top_bar.regex_type_select.cycle_box.option_changed.connect(
        [this](std::string option) { this->set_regex_type(option); });

    // Add Option
    auto& opt_box = bottom_bar.options_and_reference.options_page.options_box;
    opt_box.option_enabled.connect(
        [this](std::regex::flag_type option) { this->add_option(option); });

    // Remove Option
    opt_box.option_disabled.connect(
        [this](std::regex::flag_type option) { this->remove_option(option); });

    // Submatch selection
    target_text_section.highlight_and_scroll.tb_highlight.clicked_at_index
        .connect([this](std::size_t text_index) {
            this->set_matchbox_text(text_index);
        });
}

void Regex_explore_widget::clear_displays() {
    target_text_section.highlight_and_scroll.tb_highlight
        .clear_all_highlights();
    bottom_bar.match_page.match_box.clear();
    top_bar.regex_enter.regex_edit.brush.remove_background();
    bottom_bar.match_page.set_match_count(regex_engine_.match_count());
}

void Regex_explore_widget::update_displays() {
    auto& highlight_box = target_text_section.highlight_and_scroll.tb_highlight;
    highlight_box.clear_all_highlights();
    for (std::size_t i{0}; i < regex_engine_.match_count(); ++i) {
        highlight_box.add_highlight(regex_engine_.get_match(i).full);
    }
    bottom_bar.match_page.set_match_count(regex_engine_.match_count());
}

void Regex_explore_widget::set_target_text(const std::string& text) {
    this->clear_displays();
    try {
        regex_engine_.set_target_text(text);
    } catch (const std::regex_error&) {
        top_bar.regex_enter.regex_edit.brush.set_background(Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::set_regex_text(const std::string& regex) {
    this->clear_displays();
    try {
        regex_engine_.set_regex(regex);
    } catch (const std::regex_error&) {
        top_bar.regex_enter.regex_edit.brush.set_background(Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::set_regex_type(const std::string& option) {
    this->clear_displays();
    try {
        if (option == "ECMAScript") {
            regex_engine_.set_type(std::regex::ECMAScript);
        } else if (option == "basic") {
            regex_engine_.set_type(std::regex::basic);
        } else if (option == "extended") {
            regex_engine_.set_type(std::regex::extended);
        } else if (option == "awk") {
            regex_engine_.set_type(std::regex::awk);
        } else if (option == "grep") {
            regex_engine_.set_type(std::regex::grep);
        } else if (option == "egrep") {
            regex_engine_.set_type(std::regex::egrep);
        }
    } catch (const std::regex_error&) {
        top_bar.regex_enter.regex_edit.brush.set_background(Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::add_option(std::regex::flag_type option) {
    this->clear_displays();
    try {
        regex_engine_.set_option(option);
    } catch (const std::regex_error&) {
        top_bar.regex_enter.regex_edit.brush.set_background(Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::remove_option(std::regex::flag_type option) {
    this->clear_displays();
    try {
        regex_engine_.unset_option(option);
    } catch (const std::regex_error&) {
        top_bar.regex_enter.regex_edit.brush.set_background(Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::set_matchbox_text(std::size_t text_index) {
    std::vector<std::string> match_info{
        get_match_at(regex_engine_, text_index)};
    bottom_bar.match_page.match_box.display_match(match_info);
}

}  // namespace regex_explore
