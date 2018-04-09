#ifndef REGEX_EXPLORE_SUBMATCH_DISPLAY_HPP
#define REGEX_EXPLORE_SUBMATCH_DISPLAY_HPP
#include <cppurses/widget/widgets/text_display.hpp>

#include <cstddef>
#include <string>

#include <regex_explore/match.hpp>

namespace regex_explore {
struct Range;
class Textbox_highlight;

class Submatch_display : public cppurses::Text_display {
   public:
    Submatch_display();
    void add_match(const Match& m);
    void clear_all_matches();
    void set_current_match(std::size_t index);
    std::size_t size() const;

   private:
    std::vector<Match> matches_;
    const Textbox_highlight* text_widg_;

    std::string build_text(std::size_t index);
    std::string retrieve_text(const Range& range);
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_SUBMATCH_DISPLAY_HPP
