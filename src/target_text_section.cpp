#include <fstream>
#include <streambuf>
#include <string>

#include <cppurses/painter/color.hpp>

#include <regex_explore/target_text_section.hpp>

namespace regex_explore {

Target_text_section::Target_text_section() {
    open_file.open_requested.connect([this](std::ifstream& ifs) {
        std::string contents{std::istreambuf_iterator<char>(ifs),
                             std::istreambuf_iterator<char>()};
        tb_highlight.set_text(contents);
    });

    cppurses::set_background(open_file.filename_edit, cppurses::Color::Black);
    cppurses::set_foreground(open_file.filename_edit, cppurses::Color::White);
    open_file.filename_edit.set_ghost_color(cppurses::Color::Light_gray);
}

}  // namespace regex_explore
