#include <regex_explore/submatch_display.hpp>

#include <cstddef>
#include <sstream>
#include <string>

#include <cppurses/painter/color.hpp>
#include <cppurses/painter/utility/wchar_to_bytes.hpp>
#include <cppurses/widget/widgets/textbox.hpp>

#include <regex_explore/textbox_highlight.hpp>

namespace regex_explore {

Submatch_display::Submatch_display(const Textbox_highlight* highlight_box)
    : text_widg_{highlight_box} {
    this->cppurses::Textbox::disable_input();
    // cppurses::set_background(*this, cppurses::Color::Blue);
    // cppurses::set_foreground(*this, cppurses::Color::Black);
}

void Submatch_display::add_match(const Match& m) {
    matches_.push_back(m);
}

void Submatch_display::clear_all_matches() {
    matches_.clear();
    this->cppurses::Text_display::clear();
}

void Submatch_display::set_current_match(std::size_t index) {
    if (index >= this->Submatch_display::size()) {
        return;
    }
    this->set_text(this->build_text(index));
}

void Submatch_display::set_match_from_text_index(std::size_t text_index) {
    for (std::size_t i{0}; i < matches_.size(); ++i) {
        if (text_index >= matches_[i].entire.index &&
            text_index < matches_[i].entire.index + matches_[i].entire.length) {
            this->set_current_match(i);
        }
    }
}

std::size_t Submatch_display::size() const {
    return matches_.size();
}

std::string Submatch_display::retrieve_text(const Range& range) {
    std::string result;
    for (std::size_t i{0}; i < range.length; ++i) {
        cppurses::Glyph glyph{text_widg_->glyph_at(range.index + i)};
        std::string ch{cppurses::utility::wchar_to_bytes(glyph)};
        result.append(ch);
    }
    return result;
}

std::string Submatch_display::build_text(std::size_t index) {
    std::stringstream ss;
    // Entire Match
    ss << this->retrieve_text(matches_[index].entire);
    ss << '\n';

    // Submatches
    for (std::size_t i{0}; i < matches_[index].submatches.size(); ++i) {
        ss << "Group " << i + 1 << ": ";
        ss << this->retrieve_text(matches_[index].submatches[i]) << '\n';
    }
    std::string result{ss.str()};
    result.pop_back();
    return result;
}

}  // namespace regex_explore
