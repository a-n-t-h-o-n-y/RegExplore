#include <cppurses/cppurses.hpp>

#include "regex_explore_widget.hpp"

struct RegExplore : cppurses::Vertical_layout {
    using Titlebar = cppurses::Titlebar;
    using RegWidg = regex_explore::Regex_explore_widget;

    Titlebar& title{this->make_child<Titlebar>("RegExplore")};
    RegWidg& regexplore{this->make_child<RegWidg>()};
};

int main(int argc, const char* argv[]) {
    cppurses::System sys;

    RegExplore re;

    sys.set_head(&re);

    return sys.run();
}
