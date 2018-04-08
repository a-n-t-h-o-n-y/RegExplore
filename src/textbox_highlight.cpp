#include <regex_explore/textbox_highlight.hpp>

#include <cstddef>

#include <cppurses/painter/glyph.hpp>

#include <regex_explore/range.hpp>

namespace regex_explore {

Textbox_highlight::Textbox_highlight() : Textbox("Target Text") {
    cppurses::enable_border(*this);
}

void Textbox_highlight::set_highlight(cppurses::Color color) {
    highlight_color_ = color;
    this->update();
}

void Textbox_highlight::add_highlight(const Range& range) {
    for (std::size_t i{0}; i < range.length; ++i) {
        std::size_t highlight_index{range.index + i};
        if (highlight_index < this->contents_size()) {
            this->glyph_at(highlight_index)
                .brush.set_background(highlight_color_);
        }
    }
    this->update();
}

void Textbox_highlight::remove_highlight(const Range& range) {
    for (std::size_t i{0}; i < range.length; ++i) {
        std::size_t highlight_index{range.index + i};
        if (highlight_index < this->contents_size()) {
            this->glyph_at(highlight_index).brush.remove_background();
        }
    }
}

void Textbox_highlight::clear_all_highlights() {
    this->remove_highlight(Range{0, this->contents_size()});
    this->update();
}

}  // namespace regex_explore
