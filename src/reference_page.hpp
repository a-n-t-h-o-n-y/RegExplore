#ifndef REGEX_EXPLORE_REFERENCE_PAGE_HPP
#define REGEX_EXPLORE_REFERENCE_PAGE_HPP
#include <cppurses/widget/layouts/vertical.hpp>
#include <cppurses/widget/pipe.hpp>
#include <cppurses/widget/widgets/button.hpp>
#include <cppurses/widget/widgets/label.hpp>
#include <cppurses/widget/widgets/textbox.hpp>

namespace regex_explore {

class Reference_page : public cppurses::layout::Vertical<> {
   public:
    Reference_page()
    {
        using namespace cppurses::pipe;
        using cppurses::Color;

        *this | hide_cursor();
        label | bg(Color::Light_gray) | fg(Color::Black) | align_center();

        reference_text.disable_input();
        reference_text.set_contents(regex_reference);

        change_page | fixed_height(1) | bg(Color::Blue) | fg(Color::White);
    }

   public:
    cppurses::HLabel& label = make_child<cppurses::HLabel>({"Reference"});
    cppurses::Textbox& reference_text = make_child<cppurses::Textbox>();
    cppurses::Button& change_page = make_child<cppurses::Button>("> Options <");

   private:
    inline static std::string const regex_reference = R"(BRACKETS
[abc]  Any char a, b or c
[^abc] Any char not in the brackets
[0-9]  Any char in the range
[^0-9] Any char not in the range

METACHARACTERS
.    Single char, except \n
\w   Word char(alph-num and _)
\W   Non-word char
\d   Digit
\D   Non-digit char
\s   Whitespace char
\S   Non-whitespace char
\b   Matches a word boundary
\B   Matches a non-word boundary
[\b] Backspace char
\0   NUL char
\n   New line char
\f   Form feed char
\r   Carriage return char
\t   Tab char
\v   Vertical tab char
\cX  Matches ctrl char X
\x   Matches xth sub-expression
\    Escape a special char to a literal
\xxx    Char specified by octal xxx
\xdd    Char specified by hex dd
\uxxxx  Unicode specified by hex xxxx

QUANTIFIERS
n+     At least one n
n*     Zero or more n
n?     Zero or one n
n{X}   Sequence of X n's
n{X,Y} Sequence of X to Y n's
n{X,}  Sequence of at least X n's
n$     String with n at end
^n     String with n at beginning
x(?=n) Matches x if followed by n
x(?!n) Matches x if not followed by n
(x)    Matches x, remembers it
(?:x)  Matches x, does not remember it
x|y    Either x or y, order matters)";
};

}  // namespace regex_explore
#endif  // REGEX_EXPLORE_REFERENCE_PAGE_HPP
