#ifndef REGEX_EXPLORE_MATCH_PAGE_HPP
#define REGEX_EXPLORE_MATCH_PAGE_HPP
#include <cstddef>
#include <string>

#include <cppurses/widget/layouts/vertical.hpp>
#include <cppurses/widget/pipe.hpp>
#include <cppurses/widget/widgets/label.hpp>

#include "match_box.hpp"

namespace regex_explore {

class Match_page : public cppurses::layout::Vertical<> {
   public:
    cppurses::HLabel& label = make_child<cppurses::HLabel>({L"Matches(0)"});
    Match_box& match_box    = make_child<Match_box>();

   public:
    Match_page()
    {
        using namespace cppurses;
        using namespace cppurses::pipe;

        *this | east_border();
        label | bg(Color::Light_gray) | fg(Color::Black) | align_center();
    }

   public:
    void set_match_count(std::size_t count)
    {
        label.set_text(L"Matches(" + std::to_wstring(count) + L")");
    }
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_MATCH_PAGE_HPP
