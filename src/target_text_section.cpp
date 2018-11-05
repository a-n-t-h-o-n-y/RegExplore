#include "target_text_section.hpp"

#include <fstream>
#include <streambuf>
#include <string>

#include <cppurses/painter/color.hpp>

namespace regex_explore {

Target_text_section::Target_text_section() {
    open_file.open_requested.connect([this](std::ifstream& ifs) {
        std::string contents{std::istreambuf_iterator<char>(ifs),
                             std::istreambuf_iterator<char>()};
        highlight_and_scroll.tb_highlight.set_text(contents);
    });

    set_background(open_file.filename_edit, cppurses::Color::Black);
    set_foreground(open_file.filename_edit, cppurses::Color::White);
    open_file.filename_edit.set_ghost_color(cppurses::Color::Light_gray);
}

}  // namespace regex_explore
