#include <regex_explore/submatch_display.hpp>

#include <cstddef>
#include <sstream>
#include <string>

#include <cppurses/painter/utility/wchar_to_bytes.hpp>

#include <regex_explore/textbox_highlight.hpp>

namespace regex_explore {

Submatch_display::Submatch_display() {}

void Submatch_display::add_match(const Match& m) {
    matches_.push_back(m);
}

void Submatch_display::clear_all_matches() {
    matches_.clear();
    this->cppurses::Text_display::clear();
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
    return ss.str();
}

void Submatch_display::set_current_match(std::size_t index) {
    if (index >= this->Submatch_display::size()) {
        return;
    }
    this->set_text(this->build_text(index));
    this->update();
}

std::size_t Submatch_display::size() const {
    return matches_.size();
}

}  // namespace regex_explore
