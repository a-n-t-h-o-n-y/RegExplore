#include <regex_explore/submatch_display.hpp>

#include <cstddef>
#include <sstream>
#include <string>

#include <cppurses/painter/utility/wchar_to_bytes.hpp>

#include <regex_explore/textbox_highlight.hpp>

// #include <utility/log.hpp>  // temp

namespace regex_explore {

Submatch_display::Submatch_display(const Textbox_highlight* highlight_box)
    : text_widg_{highlight_box} {}

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
        // Never being called, maybe matches_.size() is zero?
        // utility::Log l;
        // l << "text_index: " << text_index << std::endl;
        // l << "begin: " << matches_[i].entire.index << std::endl;
        // l << "end: " << matches_[i].entire.index + matches_[i].entire.length
        //   << std::endl;
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
    return ss.str();
}

}  // namespace regex_explore
