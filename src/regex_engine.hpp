#ifndef REGEXPLORE_REGEX_ENGINE_HPP
#define REGEXPLORE_REGEX_ENGINE_HPP
#include <cstddef>
#include <regex>
#include <string>
#include <vector>

#include "match.hpp"

namespace regex_explore {

/// Performs a regular expression search and provides results.
class Regex_engine {
   public:
    using Match_container_t = std::vector<Match>;

    /// Set the target text for the regex, update the match results.
    void set_target_text(std::string target_text);

    /// View the target text for the regex.
    const std::string& get_target_text() const;

    /// Set the regex string, update the match results.
    void set_regex(std::string regex_text);

    /// View the regex text for the regex.
    const std::string& get_regex_text() const;

    /// Set the regex type, update the match results.
    void set_type(std::regex::flag_type type);

    /// Retrieve the regex type.
    std::regex::flag_type get_type() const;

    /// Set a regex option, update the match results.
    void set_option(std::regex::flag_type option);

    /// Unset a regex option, update the match results.
    void unset_option(std::regex::flag_type option);

    /// Retrieve the options set for the regex.
    std::regex::flag_type get_options() const;

    /// Return the number of matches found on the target text.
    std::size_t match_count() const;

    /// Retrieve a particular Match(a set of `Range`s over the target text).
    /** Throws std::out_of_range if out of bounds. */
    Match get_match(std::size_t match_index) const;

    /// Retrieve the entire container of Match objects.
    const Match_container_t& get_matches() const;

   private:
    std::string target_text_;
    std::string regex_text_;
    std::regex::flag_type regex_type_;
    std::regex::flag_type options_;

    // Results of Regex Search
    Match_container_t matches_;

    // Performs Regex Search
    void update_results();
};

}  // namespace regex_explore
#endif  // REGEXPLORE_REGEX_ENGINE_HPP
