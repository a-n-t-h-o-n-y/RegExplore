#include "regex_explore_widget.hpp"

#include <cstddef>
#include <regex>
#include <string>
#include <vector>

#include <cppurses/painter/color.hpp>
#include <cppurses/painter/glyph_string.hpp>

#include "option_flag.hpp"
#include "type_flag.hpp"

using cppurses::Glyph_string;

namespace regex_explore {

Regex_explore_widget::Regex_explore_widget() {
    regex_engine_.set_text(
        target_text_section.highlight_and_scroll.tb_highlight.contents().str());
    regex_engine_.set_regex(top_bar.regex_enter.regex_edit.contents().str());

    target_text_section.height_policy.stretch(3);
    this->update_displays();

    // Change Target Text
    target_text_section.highlight_and_scroll.tb_highlight.text_changed.connect(
        [this](const Glyph_string& gs) { this->set_target_text(gs.str()); });

    // Change Regex
    top_bar.regex_enter.regex_edit.text_changed.connect(
        [this](const Glyph_string& gs) { this->set_regex_text(gs.str()); });

    // Change Regex Type
    top_bar.regex_type_select.cycle_box.option_changed.connect(
        [this](std::string option) { this->set_regex_type(option); });

    // Add Option
    auto& opt_box = bottom_bar.options_and_reference.options_page.options_box;
    opt_box.option_enabled.connect(
        [this](Option_flag option) { this->add_option(option); });

    // Remove Option
    opt_box.option_disabled.connect(
        [this](Option_flag option) { this->remove_option(option); });

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
        highlight_box.add_highlight(regex_engine_.get_match(i).entire);
    }
    bottom_bar.match_page.set_match_count(regex_engine_.match_count());
}

void Regex_explore_widget::set_target_text(const std::string& text) {
    this->clear_displays();
    try {
        regex_engine_.set_text(text);
    } catch (const std::regex_error&) {
        set_background(top_bar.regex_enter.regex_edit, cppurses::Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::set_regex_text(const std::string& regex) {
    this->clear_displays();
    try {
        regex_engine_.set_regex(regex);
    } catch (const std::regex_error&) {
        set_background(top_bar.regex_enter.regex_edit, cppurses::Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::set_regex_type(const std::string& option) {
    this->clear_displays();
    try {
        if (option == "ECMAScript") {
            regex_engine_.set_type(Type_flag::ECMAScript);
        } else if (option == "basic") {
            regex_engine_.set_type(Type_flag::basic);
        } else if (option == "extended") {
            regex_engine_.set_type(Type_flag::extended);
        } else if (option == "awk") {
            regex_engine_.set_type(Type_flag::awk);
        } else if (option == "grep") {
            regex_engine_.set_type(Type_flag::grep);
        } else if (option == "egrep") {
            regex_engine_.set_type(Type_flag::egrep);
        }
    } catch (const std::regex_error&) {
        set_background(top_bar.regex_enter.regex_edit, cppurses::Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::add_option(Option_flag option) {
    this->clear_displays();
    try {
        regex_engine_.set_option(option);
    } catch (const std::regex_error&) {
        set_background(top_bar.regex_enter.regex_edit, cppurses::Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::remove_option(Option_flag option) {
    this->clear_displays();
    try {
        regex_engine_.unset_option(option);
    } catch (const std::regex_error&) {
        set_background(top_bar.regex_enter.regex_edit, cppurses::Color::Red);
        return;
    }
    this->update_displays();
}

void Regex_explore_widget::set_matchbox_text(std::size_t text_index) {
    std::vector<std::string> match_info{
        regex_engine_.get_match_strings(text_index)};
    bottom_bar.match_page.match_box.display_match(match_info);
}

}  // namespace regex_explore
