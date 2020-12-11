#ifndef REGEX_EXPLORE_MATCH_BOX_HPP
#define REGEX_EXPLORE_MATCH_BOX_HPP
#include <sstream>
#include <string>

#include <cppurses/painter/glyph_string.hpp>
#include <cppurses/widget/widgets/textbox.hpp>

#include "match.hpp"

namespace regex_explore {

class Match_box : public cppurses::Textbox {
   public:
    Match_box() { this->Textbox::disable_input(); }

   public:
    void display_match(Match const& m) { this->set_contents(make_display(m)); }

   private:
    static auto make_display(Match const& m) -> cppurses::Glyph_string
    {
        auto ss = std::ostringstream{};
        ss << "Full Match: " << m.full << '\n';
        for (auto i = 0uL; i < m.submatches.size(); ++i)
            ss << "Group " << i + 1 << ": " << m.submatches[i] << '\n';
        auto result = ss.str();
        result.pop_back();
        return result;
    }
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_MATCH_BOX_HPP
