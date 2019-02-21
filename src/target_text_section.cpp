#include "target_text_section.hpp"

#include <fstream>
#include <streambuf>
#include <string>

#include <cppurses/painter/color.hpp>

using namespace cppurses;

namespace regex_explore {

Target_text_section::Target_text_section() {
    open_file.open_requested.connect([this](std::ifstream& ifs) {
        std::string contents{std::istreambuf_iterator<char>(ifs),
                             std::istreambuf_iterator<char>()};
        highlight_and_scroll.tb_highlight.set_contents(contents);
    });

    open_file.filename_edit.brush.set_background(Color::Black);
    open_file.filename_edit.brush.set_foreground(Color::White);
    open_file.filename_edit.set_ghost_color(Color::Light_gray);
}
}  // namespace regex_explore
