#ifndef REGEX_EXPLORE_BOTTOM_BAR_HPP
#define REGEX_EXPLORE_BOTTOM_BAR_HPP
#include <cppurses/widget/layouts/horizontal_layout.hpp>
#include <cppurses/widget/widgets/text_display.hpp>

namespace regex_explore {
class Bottom_bar : public cppurses::Horizontal_layout {
   public:
    Bottom_bar();

   private:
    cppurses::Text_display& sub_matches_{
        this->make_child<cppurses::Text_display>("SubMatches")};
    cppurses::Text_display& match_info_{
        this->make_child<cppurses::Text_display>("Full Match and Indicies")};
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_BOTTOM_BAR_HPP
