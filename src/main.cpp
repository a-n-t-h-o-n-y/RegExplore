#include <cppurses/cppurses.hpp>

#include <regex_explore/regex_explore_widget.hpp>
#include <regex_explore/textbox_highlight.hpp>
#include <regex_explore/top_bar.hpp>

int main(int argc, const char* argv[]) {
    cppurses::System sys;

    regex_explore::Regex_explore_widget widg;

    sys.set_head(&widg);

    return sys.run();
}
