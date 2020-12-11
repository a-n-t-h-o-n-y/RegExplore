#include "regex_engine.hpp"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "match.hpp"

namespace {
using namespace regex_explore;

auto get_string_view(std::ssub_match const& submatch) -> std::string_view
{
    std::size_t const length = std::distance(submatch.first, submatch.second);
    return {&*submatch.first, length};
}

template <typename Iter>
auto get_submatches(Iter begin, Iter end) -> std::vector<std::string_view>
{
    auto result = std::vector<std::string_view>{};
    std::transform(begin, end, std::back_inserter(result), get_string_view);
    return result;
}

auto extract_match(std::smatch const& match) -> Match
{
    auto begin     = std::begin(match);
    auto const end = std::end(match);

    auto const full_match = get_string_view(*begin);
    std::advance(begin, 1);
    return {full_match,
            {static_cast<std::size_t>(match.position(0)),
             static_cast<std::size_t>(match.length(0))},
            get_submatches(begin, end)};
}

auto regex_iter(std::string const& target, std::regex const& regex)
    -> std::sregex_iterator
{
    return {std::begin(target), std::end(target), regex};
}

auto regex_iter() -> std::sregex_iterator { return {}; }

auto find_matches(std::string const& target, std::regex const& regex)
    -> std::vector<Match>
{
    auto result = std::vector<Match>{};
    std::transform(
        regex_iter(target, regex), regex_iter(), std::back_inserter(result),
        [](std::smatch const& match) { return extract_match(match); });
    return result;
}

}  // namespace

namespace regex_explore {

void Regex_engine::update_matches()
{
    if (regex_text_.empty() || target_text_.empty())
        return;
    // Throws std::regex_error if regex_text_ invalid.
    auto regex = std::regex{regex_text_, regex_type_ | options_};
    matches_   = find_matches(target_text_, regex);
}

}  // namespace regex_explore
