#include "textbox_highlight.hpp"

#include <cstddef>
#include <cstdint>

#include <cppurses/painter/attribute.hpp>
#include <cppurses/painter/brush.hpp>
#include <cppurses/painter/glyph.hpp>
#include <cppurses/system/mouse_data.hpp>
#include <cppurses/widget/widget_free_functions.hpp>

#include "range.hpp"

namespace regex_explore {

Textbox_highlight::Textbox_highlight() : Textbox("Target Text") {
    set_background(*this, cppurses::Color::White);
    set_foreground(*this, cppurses::Color::Black);
}

void Textbox_highlight::set_highlight_color(cppurses::Color color) {
    highlight_color_ = color;
    this->update();
}

void Textbox_highlight::add_highlight(const Range& range) {
    for (std::size_t i{0}; i < range.length; ++i) {
        std::size_t highlight_index{range.index + i};
        if (highlight_index < this->contents_size()) {
            this->glyph_at(highlight_index)
                .brush.set_background(highlight_color_);
            if (i == 0) {
                this->glyph_at(highlight_index)
                    .brush.add_attributes(cppurses::Attribute::Underline);
            }
        }
    }
    this->update();
}

void Textbox_highlight::remove_highlight(const Range& range) {
    for (std::size_t i{0}; i < range.length; ++i) {
        std::size_t highlight_index{range.index + i};
        if (highlight_index < this->contents_size()) {
            this->glyph_at(highlight_index).brush.remove_background();
            this->glyph_at(highlight_index).brush.clear_attributes();
        }
    }
}

void Textbox_highlight::clear_all_highlights() {
    this->remove_highlight(Range{0, this->contents_size()});
    this->update();
}

bool Textbox_highlight::mouse_press_event(const cppurses::Mouse_data& mouse) {
    if (mouse.button == cppurses::Mouse_button::Left) {
        clicked_at_index(this->index_at(mouse.local));
    }
    return cppurses::Textbox::mouse_press_event(mouse);
}
}  // namespace regex_explore
