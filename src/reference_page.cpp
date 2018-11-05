#include "reference_page.hpp"

#include <string>

#include <cppurses/painter/color.hpp>
#include <cppurses/widget/size_policy.hpp>
#include <cppurses/widget/widget_free_functions.hpp>

namespace {

std::string regex_reference{R"(BRACKETS
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
x|y    Either x or y, order matters)"};

}  // namespace

namespace regex_explore {

Reference_page::Reference_page() {
    label.set_alignment(cppurses::Alignment::Center);
    set_background(label, cppurses::Color::Light_gray);
    set_foreground(label, cppurses::Color::Black);

    reference_text.disable_input();
    reference_text.set_text(regex_reference);

    change_page.height_policy.type(cppurses::Size_policy::Fixed);
    change_page.height_policy.hint(1);
    set_background(change_page, cppurses::Color::Blue);
    set_foreground(change_page, cppurses::Color::White);
}

}  // namespace regex_explore
