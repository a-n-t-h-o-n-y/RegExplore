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

void Textbox_highlight::add_range(const Range& range) {
    highlight_ranges_.push_back(range);
    this->update();
}

void Textbox_highlight::clear_ranges() {
    highlight_ranges_.clear();
    this->update();
}

void Textbox_highlight::remove_range(std::size_t index) {
    if (index >= highlight_ranges_.size()) {
        highlight_ranges_.erase(std::begin(highlight_ranges_) + index);
        this->update();
    }
}

bool Textbox_highlight::paint_event() {
    // Move to its own function to be called by client of Textbox_highlight
    // Unneccessary to call for resizes etc...
    // clear all background colors on glyphs in *this
    for (cppurses::Glyph& g : this->contents()) {
        g.brush.remove_background();
    }
    // Set highlight background for each glyph.
    for (Range r : highlight_ranges_) {
        for (std::size_t i{0}; i < r.length; ++i) {
            std::size_t highlight_index{r.index + i};
            if (highlight_index < this->contents_size()) {
                this->glyph_at(highlight_index)
                    .brush.set_background(highlight_color_);
            }
        }
    }
    return Text_display::paint_event();
}

}  // namespace regex_explore
