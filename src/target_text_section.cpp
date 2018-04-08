#include <fstream>
#include <streambuf>
#include <string>

#include <regex_explore/target_text_section.hpp>

namespace regex_explore {

Target_text_section::Target_text_section() {
    open_file.open_requested.connect([this](std::ifstream& ifs) {
        std::string contents{std::istreambuf_iterator<char>(ifs),
                             std::istreambuf_iterator<char>()};
        tb_highlight.set_text(contents);
    });
}

}  // namespace regex_explore
