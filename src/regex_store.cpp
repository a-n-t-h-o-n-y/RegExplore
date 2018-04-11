#include <regex_explore/regex_store.hpp>

#include <algorithm>
#include <cstddef>
#include <regex>
#include <string>
#include <vector>

#include <regex_explore/option_flag.hpp>
#include <regex_explore/range.hpp>
#include <regex_explore/type_flag.hpp>

// LOCAL UTILITY - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
namespace {
using namespace regex_explore;

bool contains(const std::vector<Option_flag>& options, Option_flag option) {
    return std::find(std::begin(options), std::end(options), option) !=
           std::end(options);
}

auto find(const std::vector<Option_flag>& options, Option_flag option) {
    return std::find(std::begin(options), std::end(options), option);
}

std::regex::flag_type options_to_mask(const std::vector<Option_flag>& flags) {
    std::regex::flag_type result{static_cast<std::regex::flag_type>(0)};
    for (Option_flag flag : flags) {
        std::regex::flag_type flag_mask{};
        switch (flag) {
            case Option_flag::case_insensitive:
                flag_mask = std::regex::icase;
                break;
            case Option_flag::no_subexpressions:
                flag_mask = std::regex::nosubs;
                break;
            case Option_flag::optimize:
                flag_mask = std::regex::optimize;
                break;
            case Option_flag::collate:
                flag_mask = std::regex::collate;
                break;
            default:
                flag_mask = static_cast<std::regex::flag_type>(0);
        }
        result |= flag_mask;
    }
    return result;
}

std::regex::flag_type type_to_mask(Type_flag type) {
    std::regex::flag_type type_mask;
    switch (type) {
        case Type_flag::ECMAScript:
            type_mask = std::regex::ECMAScript;
            break;
        case Type_flag::basic:
            type_mask = std::regex::basic;
            break;
        case Type_flag::extended:
            type_mask = std::regex::extended;
            break;
        case Type_flag::awk:
            type_mask = std::regex::awk;
            break;
        case Type_flag::grep:
            type_mask = std::regex::grep;
            break;
        case Type_flag::egrep:
            type_mask = std::regex::egrep;
            break;
        default:
            type_mask = static_cast<std::regex::flag_type>(0);
    }
    return type_mask;
}

}  // namespace

namespace regex_explore {

Regex_store::Regex_store(const std::string& target_text,
                         const std::string& regex_text)
    : target_text_{target_text}, regex_text_{regex_text} {}

// STATE CHANGES - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Regex_store::set_text(std::string target_text) {
    target_text_ = target_text;
    this->update_results();
}

void Regex_store::set_regex(std::string regex_text) {
    regex_text_ = regex_text;
    this->update_results();
}

void Regex_store::set_type(Type_flag type) {
    regex_type_ = type;
    this->update_results();
}

void Regex_store::set_option(Option_flag option) {
    if (!contains(regex_options_, option)) {
        regex_options_.push_back(option);
    }
    this->update_results();
}

void Regex_store::unset_option(Option_flag option) {
    auto at = find(regex_options_, option);
    if (at != std::end(regex_options_)) {
        regex_options_.erase(at);
    }
    this->update_results();
}

// RESULTS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Throws std::out_of_range if out of bounds.
Match Regex_store::get_match(std::size_t match_index) const {
    return matches_.at(match_index);
}

std::vector<std::string> Regex_store::get_match_strings(
    std::size_t text_index) const {
    for (std::size_t i{0}; i < this->match_count(); ++i) {
        if (text_index >= matches_[i].entire.index &&
            text_index < matches_[i].entire.index + matches_[i].entire.length) {
            return this->get_strings(i);
        }
    }
    return std::vector<std::string>();
}

std::size_t Regex_store::match_count() const {
    return matches_.size();
}

// IMPLEMENTATION - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Regex_store::update_results() {
    matches_.clear();
    if (regex_text_.empty() || target_text_.empty()) {
        return;
    }

    // Create Regex object from parameters.
    std::regex::flag_type type_flag{type_to_mask(regex_type_)};
    std::regex::flag_type option_flags{options_to_mask(regex_options_)};

    // Throws std::regex_error if regex_text_ invalid.
    std::regex regex{regex_text_, type_flag | option_flags};

    // Perform search and store results in matches_ vector.
    auto begin = std::begin(target_text_);
    auto end = std::end(target_text_);
    using RegIter = std::sregex_iterator;
    for (RegIter iter(begin, end, regex); iter != RegIter(); ++iter) {
        std::smatch regex_match{*iter};
        // Entire Match
        Range entire{static_cast<std::size_t>(regex_match.position(0)),
                     static_cast<std::size_t>(regex_match.length(0))};

        Match match_data{entire};
        // Submatches
        for (std::size_t i{1}; i < regex_match.size(); ++i) {
            Range sub_range{static_cast<std::size_t>(regex_match.position(i)),
                            static_cast<std::size_t>(regex_match.length(i))};
            match_data.submatches.push_back(sub_range);
        }
        matches_.push_back(match_data);
    }
}

std::vector<std::string> Regex_store::get_strings(
    std::size_t match_index) const {
    std::vector<std::string> results;
    const Match& match{matches_[match_index]};

    // Entire Match
    results.push_back(
        target_text_.substr(match.entire.index, match.entire.length));

    // SubMatches
    for (Range submatch : match.submatches) {
        results.push_back(target_text_.substr(submatch.index, submatch.length));
    }
    return results;
}

}  // namespace regex_explore
