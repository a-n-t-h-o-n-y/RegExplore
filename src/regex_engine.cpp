#include "regex_engine.hpp"

#include <algorithm>
#include <cstddef>
#include <regex>
#include <string>
#include <vector>

#include "match.hpp"
#include "range.hpp"

namespace {
using namespace regex_explore;
Range get_range(const std::smatch& match_results, std::size_t index) {
    return {static_cast<std::size_t>(match_results.position(index)),
            static_cast<std::size_t>(match_results.length(index))};
}

std::vector<Range> extract_submatches(const std::smatch& match_results) {
    std::vector<Range> sub_matches;
    for (std::size_t i{1}; i < match_results.size(); ++i) {
        sub_matches.push_back(get_range(match_results, i));
    }
    return sub_matches;
}

Match extract_match(const std::smatch& match_results) {
    Range full_match{get_range(match_results, 0)};
    return {full_match, extract_submatches(match_results)};
}

std::sregex_iterator regex_iter(const std::string& target,
                                const std::regex& regex) {
    return {std::begin(target), std::end(target), regex};
}

std::sregex_iterator regex_iter() {
    return {};
}

std::vector<Match> find_matches(const std::string& target,
                                const std::regex& regex) {
    std::vector<Match> result;
    std::transform(
        regex_iter(target, regex), regex_iter(), std::back_inserter(result),
        [](const std::smatch& match) { return extract_match(match); });
    return result;
}
}  // namespace

namespace regex_explore {

void Regex_engine::set_target_text(std::string target_text) {
    target_text_ = std::move(target_text);
    this->update_results();
}

const std::string& Regex_engine::get_target_text() const {
    return target_text_;
}

void Regex_engine::set_regex(std::string regex_text) {
    regex_text_ = std::move(regex_text);
    this->update_results();
}

const std::string& Regex_engine::get_regex_text() const {
    return regex_text_;
}

void Regex_engine::set_type(std::regex::flag_type type) {
    regex_type_ = type;
    this->update_results();
}

std::regex::flag_type Regex_engine::get_type() const {
    return regex_type_;
}

void Regex_engine::set_option(std::regex::flag_type option) {
    options_ |= option;
    this->update_results();
}

void Regex_engine::unset_option(std::regex::flag_type option) {
    options_ &= ~option;
    this->update_results();
}

std::regex::flag_type Regex_engine::get_options() const {
    return options_;
}

std::size_t Regex_engine::match_count() const {
    return matches_.size();
}

Match Regex_engine::get_match(std::size_t match_index) const {
    return matches_.at(match_index);
}

const Regex_engine::Match_container_t& Regex_engine::get_matches() const {
    return matches_;
}

void Regex_engine::update_results() {
    if (regex_text_.empty() || target_text_.empty()) {
        return;
    }
    // Throws std::regex_error if regex_text_ invalid.
    std::regex regex{regex_text_, regex_type_ | options_};
    matches_ = find_matches(target_text_, regex);
}

}  // namespace regex_explore
