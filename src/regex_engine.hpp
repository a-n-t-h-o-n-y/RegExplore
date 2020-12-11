#ifndef REGEXPLORE_REGEX_ENGINE_HPP
#define REGEXPLORE_REGEX_ENGINE_HPP
#include <cstddef>
#include <regex>
#include <string>
#include <vector>

#include "match.hpp"

namespace regex_explore {

/// Performs a regular expression search and provides results.
/** All Matches point to strings owned by *this. */
class Regex_engine {
   public:
    using Match_container_t = std::vector<Match>;

   public:
    /// Set the target text for the regex, update the match results.
    void set_target_text(std::string target_text)
    {
        target_text_ = std::move(target_text);
        this->update_matches();
    }

    /// Return a reference to the target text for.
    auto get_target_text() const -> const std::string& { return target_text_; }

    /// Set the regex string, update the match results.
    void set_regex(std::string regex_text)
    {
        regex_text_ = std::move(regex_text);
        this->update_matches();
    }

    /// Return a reference to the regex text.
    auto get_regex_text() const -> const std::string& { return regex_text_; }

    /// Set the regex type, update the match results.
    void set_type(std::regex::flag_type type)
    {
        regex_type_ = type;
        this->update_matches();
    }

    /// Retrieve the regex type.
    auto get_type() const -> std::regex::flag_type { return regex_type_; }

    /// Set a regex option, update the match results.
    void set_option(std::regex::flag_type option)
    {
        options_ |= option;
        this->update_matches();
    }

    /// Unset a regex option, update the match results.
    void unset_option(std::regex::flag_type option)
    {
        options_ &= ~option;
        this->update_matches();
    }

    /// Retrieve the options set for the regex.
    auto get_options() const -> std::regex::flag_type { return options_; }

    /// Return the number of matches found on the target text.
    auto match_count() const -> std::size_t { return matches_.size(); }

    /// Returns an iterator to the first Match.
    auto begin() const -> std::vector<Match>::const_iterator
    {
        return std::cbegin(matches_);
    }

    /// Returns an iterator to one past the last Match.
    auto end() const -> std::vector<Match>::const_iterator
    {
        return std::cend(matches_);
    }

   private:
    std::string target_text_;
    std::string regex_text_;
    std::regex::flag_type regex_type_;
    std::regex::flag_type options_;

    // Results of Regex Search
    Match_container_t matches_;

    /// Performs Regex Search and updates the match container.
    /** Will throw std::regex_error if the regex_text_ is invalid. */
    void update_matches();
};

}  // namespace regex_explore
#endif  // REGEXPLORE_REGEX_ENGINE_HPP
