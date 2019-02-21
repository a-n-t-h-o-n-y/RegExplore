#include <cppurses/system/system.hpp>
#include <cppurses/widget/layouts/vertical.hpp>
#include <cppurses/widget/widgets/titlebar.hpp>

#include "regex_explore_widget.hpp"

using namespace cppurses;

namespace {

using Reg_widg_t = regex_explore::Regex_explore_widget;

struct RegExplore : layout::Vertical {
    Titlebar& title{this->make_child<Titlebar>("RegExplore")};
    Reg_widg_t& regexplore{this->make_child<Reg_widg_t>()};
};

}  // namespace

int main() {
    System sys;
    return sys.run<RegExplore>();
}
