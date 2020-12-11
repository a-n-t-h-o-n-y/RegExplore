#include "regex_explore_widget.hpp"

#include <cstddef>
#include <optional>
#include <regex>
#include <string>
#include <vector>

#include <cppurses/painter/color.hpp>
#include <cppurses/painter/glyph_string.hpp>

#include "regex_engine.hpp"

using namespace cppurses;

namespace {
using namespace regex_explore;

/// Return a callable on Match that determines if \p target is a part of Match.
auto contains_char_pointer(char const* target)
{
    return [target](Match const& m) {
        return std::find_if(std::begin(m.full), std::end(m.full),
                            [target](char const& c) { return &c == target; }) !=
               std::end(m.full);
    };
}

/// Retrieves match at index within text, if there is one.
/** Returns std::nullopt if no Match exists at the given index. */
auto get_match_at(Regex_engine const& engine, std::size_t text_index)
    -> std::optional<Match>
{
    auto const& text = engine.get_target_text();
    if (text_index > text.size())
        return std::nullopt;

    char const* const target = &text[text_index];
    auto const iter          = std::find_if(engine.begin(), engine.end(),
                                   contains_char_pointer(target));
    if (iter == engine.end())
        return std::nullopt;
    return *iter;
}

}  // namespace

namespace regex_explore {

Regex_explore_widget::Regex_explore_widget()
{
    regex_engine_.set_target_text(
        target_text_section.highlight_and_scroll.tb_highlight.contents().str());
    regex_engine_.set_regex(top_bar.regex_enter.regex_edit.contents().str());

    target_text_section.height_policy.stretch(3);
    this->update_displays();

    // Change Target Text
    target_text_section.highlight_and_scroll.tb_highlight.contents_modified
        .connect([this](Glyph_string const& gs) {
            this->set_target_text(gs.str());
        });

    // Change Regex
    top_bar.regex_enter.regex_edit.contents_modified.connect(
        [this](Glyph_string const& gs) { this->set_regex_text(gs.str()); });

    // Change Regex Type
    top_bar.regex_type_select.cycle_box.option_changed.connect(
        [this](std::string option) { this->set_regex_type(option); });

    // Add Option
    auto& opt_box = bottom_bar.options_and_reference.options_page.options_box;
    opt_box.option_on.connect(
        [this](std::regex::flag_type option) { this->add_option(option); });

    // Remove Option
    opt_box.option_off.connect(
        [this](std::regex::flag_type option) { this->remove_option(option); });

    // Submatch selection
    target_text_section.highlight_and_scroll.tb_highlight.clicked_at_index
        .connect([this](std::size_t text_index) {
            this->set_matchbox_text(text_index);
        });
}

void Regex_explore_widget::clear_displays()
{
    target_text_section.highlight_and_scroll.tb_highlight
        .clear_all_highlights();
    bottom_bar.match_page.match_box.clear();
    top_bar.regex_enter.regex_edit.brush.remove_background();
    bottom_bar.match_page.set_match_count(regex_engine_.match_count());
}

void Regex_explore_widget::update_displays()
{
    auto& highlight_box = target_text_section.highlight_and_scroll.tb_highlight;
    highlight_box.clear_all_highlights();
    for (Match const& m : regex_engine_)
        highlight_box.add_highlight(m.range);
    bottom_bar.match_page.set_match_count(regex_engine_.match_count());
}

void Regex_explore_widget::set_target_text(std::string const& text)
{
    this->clear_displays();
    try {
        regex_engine_.set_target_text(text);
    }
    catch (std::regex_error const&) {
        top_bar.regex_enter.regex_edit.brush.set_background(Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::set_regex_text(std::string const& regex)
{
    this->clear_displays();
    try {
        regex_engine_.set_regex(regex);
    }
    catch (std::regex_error const&) {
        top_bar.regex_enter.regex_edit.brush.set_background(Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::set_regex_type(std::string const& option)
{
    this->clear_displays();
    try {
        if (option == "ECMAScript")
            regex_engine_.set_type(std::regex::ECMAScript);
        else if (option == "basic")
            regex_engine_.set_type(std::regex::basic);
        else if (option == "extended")
            regex_engine_.set_type(std::regex::extended);
        else if (option == "awk")
            regex_engine_.set_type(std::regex::awk);
        else if (option == "grep")
            regex_engine_.set_type(std::regex::grep);
        else if (option == "egrep")
            regex_engine_.set_type(std::regex::egrep);
    }
    catch (std::regex_error const&) {
        top_bar.regex_enter.regex_edit.brush.set_background(Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::add_option(std::regex::flag_type option)
{
    this->clear_displays();
    try {
        regex_engine_.set_option(option);
    }
    catch (std::regex_error const&) {
        top_bar.regex_enter.regex_edit.brush.set_background(Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::remove_option(std::regex::flag_type option)
{
    this->clear_displays();
    try {
        regex_engine_.unset_option(option);
    }
    catch (std::regex_error const&) {
        top_bar.regex_enter.regex_edit.brush.set_background(Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::set_matchbox_text(std::size_t text_index)
{
    auto const match = get_match_at(regex_engine_, text_index);
    if (match)
        bottom_bar.match_page.match_box.display_match(*match);
}

}  // namespace regex_explore
