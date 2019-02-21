#include "textbox_highlight.hpp"

#include <cstddef>
#include <cstdint>

#include <cppurses/painter/attribute.hpp>
#include <cppurses/painter/brush.hpp>
#include <cppurses/painter/glyph.hpp>
#include <cppurses/system/events/mouse.hpp>

#include "range.hpp"

namespace {
using namespace cppurses;

Brush& brush_at(Text_display& td, std::size_t index) {
    return td.contents()[index].brush;
}

}  // namespace

namespace regex_explore {

Textbox_highlight::Textbox_highlight() : Textbox("Target Text") {
    this->brush.set_background(Color::White);
    this->brush.set_foreground(Color::Black);
}

void Textbox_highlight::set_highlight_color(cppurses::Color color) {
    highlight_color_ = color;
    this->update();
}

void Textbox_highlight::add_highlight(const Range& range) {
    std::size_t end{range.index + range.length};
    if (end > this->contents().size()) {
        return;
    }
    if (range.length != 0) {
        using cppurses::Attribute;
        brush_at(*this, range.index).add_attributes(Attribute::Underline);
    }
    for (std::size_t i{range.index}; i < end; ++i) {
        brush_at(*this, i).set_background(highlight_color_);
    }
    this->update();
}

void Textbox_highlight::remove_highlight(const Range& range) {
    std::size_t end{range.index + range.length};
    if (end > this->contents().size()) {
        return;
    }
    for (std::size_t i{range.index}; i < end; ++i) {
        brush_at(*this, i).remove_background();
        brush_at(*this, i).clear_attributes();
    }
}

void Textbox_highlight::clear_all_highlights() {
    this->remove_highlight({0, this->contents().size()});
    this->update();
}

bool Textbox_highlight::mouse_press_event(const cppurses::Mouse::State& mouse) {
    if (mouse.button == cppurses::Mouse::Button::Left) {
        clicked_at_index(this->index_at(mouse.local));
    }
    return cppurses::Textbox::mouse_press_event(mouse);
}
}  // namespace regex_explore
