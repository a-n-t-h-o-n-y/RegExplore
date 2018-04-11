#include <regex_explore/regex_explore_widget.hpp>

#include <cstddef>
#include <regex>
#include <string>

#include <cppurses/painter/color.hpp>
#include <cppurses/painter/glyph_string.hpp>
#include <cppurses/widget/widget.hpp>
#include <signals/slot.hpp>

#include <regex_explore/match.hpp>
#include <regex_explore/option_flag.hpp>
#include <regex_explore/textbox_highlight.hpp>
#include <regex_explore/type_flag.hpp>

using cppurses::Glyph_string;

namespace regex_explore {

Regex_explore_widget::Regex_explore_widget()
    : regex_store_{
          target_text_section_.highlight_and_scroll.tb_highlight.contents()
              .str(),
          top_bar_.regex_enter.regex_edit.contents().str()} {
    target_text_section_.height_policy.stretch(3);
    this->update_displays();
    // Change Target Text
    target_text_section_.highlight_and_scroll.tb_highlight.text_changed.connect(
        [this](const Glyph_string& gs) {
            this->clear_displays();
            regex_store_.set_text(gs.str());
            this->update_displays();
        });

    // Change Regex
    top_bar_.regex_enter.regex_edit.text_changed.connect(
        [this](const Glyph_string& gs) {
            this->clear_displays();
            try {
                regex_store_.set_regex(gs.str());
            } catch (const std::regex_error&) {
                set_background(top_bar_.regex_enter.regex_edit,
                               cppurses::Color::Red);
                return;
            }
            this->update_displays();
        });

    // Change Regex Type
    top_bar_.regex_type_select.cycle_box.option_changed.connect(
        [this](std::string option) {
            this->clear_displays();
            if (option == "ECMAScript") {
                regex_store_.set_type(Type_flag::ECMAScript);
            } else if (option == "basic") {
                regex_store_.set_type(Type_flag::basic);
            } else if (option == "extended") {
                regex_store_.set_type(Type_flag::extended);
            } else if (option == "awk") {
                regex_store_.set_type(Type_flag::awk);
            } else if (option == "grep") {
                regex_store_.set_type(Type_flag::grep);
            } else if (option == "egrep") {
                regex_store_.set_type(Type_flag::egrep);
            }
            this->update_displays();
        });

    // Add Option
    auto& opt_box = bottom_bar_.options_and_reference.options_page.options_box;
    opt_box.option_enabled.connect([this](Option_flag option) {
        this->clear_displays();
        regex_store_.set_option(option);
        this->update_displays();
    });

    // Remove Option
    opt_box.option_disabled.connect([this](Option_flag option) {
        this->clear_displays();
        regex_store_.unset_option(option);
        this->update_displays();
    });

    // Submatch selection
    target_text_section_.highlight_and_scroll.tb_highlight.clicked_at_index
        .connect([this](std::size_t text_index) {
            bottom_bar_.match_page.match_box.display_match(
                regex_store_.get_match_strings(text_index));
            // bottom_bar_.match_page.match_box.set_match_from_text_index(
            //     text_index);
        });
}

void Regex_explore_widget::clear_displays() {
    target_text_section_.highlight_and_scroll.tb_highlight
        .clear_all_highlights();
    bottom_bar_.match_page.match_box.clear_all_matches();
    top_bar_.regex_enter.regex_edit.brush.remove_background();
    bottom_bar_.match_page.set_match_count(regex_store_.match_count());
}

void Regex_explore_widget::update_displays() {
    auto& highlight_box =
        target_text_section_.highlight_and_scroll.tb_highlight;
    highlight_box.clear_all_highlights();
    for (std::size_t i{0}; i < regex_store_.match_count(); ++i) {
        highlight_box.add_highlight(regex_store_.get_match(i).entire);
    }
    bottom_bar_.match_page.set_match_count(regex_store_.match_count());
}

// void Regex_explore_widget::perform_search_and_update() {
//     // Get regex text.
//     std::string regex_str{top_bar_.regex_enter.regex_edit.contents().str()};
//     if (regex_str.empty()) {
//         target_text_section_.highlight_and_scroll.tb_highlight
//             .clear_all_highlights();
//         bottom_bar_.match_page.match_box.clear_all_matches();
//         top_bar_.regex_enter.regex_edit.brush.remove_background();
//         bottom_bar_.match_page.set_match_count();
//         return;
//     }

//     // Create Regex object from flags.
//     std::regex regex;
//     top_bar_.regex_enter.regex_edit.brush.remove_background();
//     this->update();
//     std::regex::flag_type flags{regex_type_};
//     flags |= regex_options_;
//     try {
//         regex.assign(regex_str, flags);
//     } catch (const std::regex_error& re) {
//         cppurses::set_background(top_bar_.regex_enter.regex_edit,
//                                  cppurses::Color::Red);
//     }

//     // Get target text.
//     std::string target_text{
//         target_text_section_.highlight_and_scroll.tb_highlight.contents()
//             .str()};

//     // Clear the current tb_highlight of ranges.
//     target_text_section_.highlight_and_scroll.tb_highlight
//         .clear_all_highlights();
//     bottom_bar_.match_page.match_box.clear_all_matches();

//     // Search target text with above regex in a loop
//     std::size_t match_count{0};
//     for (std::sregex_iterator i{std::sregex_iterator(
//              std::begin(target_text), std::end(target_text), regex)};
//          i != std::sregex_iterator(); ++i) {
//         std::smatch match{*i};
//         // Entire Match
//         Range range_entire{static_cast<std::size_t>(match.position(0)),
//                            static_cast<std::size_t>(match.length(0))};
//         target_text_section_.highlight_and_scroll.tb_highlight.add_highlight(
//             range_entire);
//         ++match_count;

//         // Submatches
//         Match match_data{range_entire};
//         for (std::size_t i{1}; i < match.size(); ++i) {
//             Range sub_range{static_cast<std::size_t>(match.position(i)),
//                             static_cast<std::size_t>(match.length(i))};
//             match_data.submatches.push_back(sub_range);
//         }
//         bottom_bar_.match_page.match_box.add_match(match_data);
//     }
//     bottom_bar_.match_page.set_match_count();
// }

}  // namespace regex_explore
