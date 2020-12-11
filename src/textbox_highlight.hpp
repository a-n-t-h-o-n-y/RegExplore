#ifndef REGEX_EXPLORER_TEXTBOX_HIGHLIGHT_HPP
#define REGEX_EXPLORER_TEXTBOX_HIGHLIGHT_HPP
#include <cstddef>

#include <signals_light/signal.hpp>

#include <cppurses/painter/brush.hpp>
#include <cppurses/painter/color.hpp>
#include <cppurses/painter/glyph.hpp>
#include <cppurses/painter/trait.hpp>
#include <cppurses/system/mouse.hpp>
#include <cppurses/widget/layouts/horizontal.hpp>
#include <cppurses/widget/pipe.hpp>
#include <cppurses/widget/point.hpp>
#include <cppurses/widget/widgets/scrollbar.hpp>
#include <cppurses/widget/widgets/textbox.hpp>

#include "match.hpp"

namespace regex_explore {

class Textbox_highlight : public cppurses::Textbox {
   public:
    Textbox_highlight() : Textbox("Target Text")
    {
        using namespace cppurses::pipe;
        *this | bg(cppurses::Color::White) | fg(cppurses::Color::Black);
    }

   public:
    /// Signal to notify of a mouse click on the text.
    sl::Signal<void(std::size_t)> clicked_at_index;

   public:
    /// Set the color to highlight matches with.
    void set_highlight_color(cppurses::Color color)
    {
        highlight_color_ = color;
        this->update();
    }

    /// Highlight a range of text on the display.
    void add_highlight(Match::Range const& r)
    {
        auto const end = r.position + r.length;
        if (end > this->contents().size())
            return;
        if (r.length != 0)
            this->contents()[r.position] | cppurses::Trait::Underline;
        for (auto i = r.position; i < end; ++i)
            this->contents()[i] | background(highlight_color_);
        this->update();
    }

    /// Remove a range of text on the display.
    void remove_highlight(Match::Range const& r)
    {
        auto const end = r.position + r.length;
        if (end > this->contents().size())
            return;
        for (auto i = r.position; i < end; ++i) {
            this->contents()[i].brush.remove_background();
            this->contents()[i].brush.clear_traits();
        }
    }

    /// Remove all highlights from the display.
    void clear_all_highlights()
    {
        this->remove_highlight({0, this->contents().size()});
        this->update();
    }

   protected:
    auto mouse_press_event(cppurses::Mouse const& m) -> bool override
    {
        if (m.button == cppurses::Mouse::Button::Left)
            clicked_at_index(this->index_at(m.local));
        return cppurses::Textbox::mouse_press_event(m);
    }

   private:
    cppurses::Color highlight_color_ = cppurses::Color::Yellow;
};

class Highlight_and_scroll : public cppurses::layout::Horizontal<> {
   public:
    Highlight_and_scroll() { link(scrollbar, tb_highlight); }

   public:
    Textbox_highlight& tb_highlight = make_child<Textbox_highlight>();
    cppurses::VScrollbar& scrollbar = make_child<cppurses::VScrollbar>();
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORER_TEXTBOX_HIGHLIGHT_HPP
