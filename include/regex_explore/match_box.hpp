#ifndef REGEX_EXPLORE_MATCH_BOX_HPP
#define REGEX_EXPLORE_MATCH_BOX_HPP
#include <cppurses/widget/widgets/textbox.hpp>

#include <cstddef>
#include <string>
#include <vector>

#include <regex_explore/match.hpp>

namespace regex_explore {
struct Range;
class Textbox_highlight;

class Match_box : public cppurses::Textbox {
   public:
    Match_box(const Textbox_highlight* highlight_box);
    void add_match(const Match& m);
    void clear_all_matches();
    std::size_t matches_count() const;

    void set_current_match(std::size_t index);
    void set_match_from_text_index(std::size_t text_index);

   private:
    std::vector<Match> matches_;
    const Textbox_highlight* text_widg_;

    std::string build_text(std::size_t index);
    std::string retrieve_text(const Range& range);
    void clear_screen();
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_MATCH_BOX_HPP
