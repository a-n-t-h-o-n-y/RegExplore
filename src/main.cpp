#include <cppurses/cppurses.hpp>

#include "regex_explore_widget.hpp"
namespace {
using Titlebar = cppurses::Titlebar;
using Reg_widg_t = regex_explore::Regex_explore_widget;

struct RegExplore : cppurses::Vertical_layout {
    Titlebar& title{this->make_child<Titlebar>("RegExplore")};
    Reg_widg_t& regexplore{this->make_child<Reg_widg_t>()};
};

}  // namespace

int main() {
    cppurses::System sys;
    RegExplore re;
    sys.set_head(&re);
    return sys.run();
}
