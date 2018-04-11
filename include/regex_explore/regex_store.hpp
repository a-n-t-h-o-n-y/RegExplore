#ifndef REGEXPLORE_REGEX_STORE_HPP
#define REGEXPLORE_REGEX_STORE_HPP
#include <cstddef>
#include <string>
#include <vector>

#include <regex_explore/match.hpp>
#include <regex_explore/option_flag.hpp>
#include <regex_explore/type_flag.hpp>

namespace regex_explore {

/// Performs a regular expression search and provides results.
class Regex_store {
   public:
    // State Change
    void set_text(std::string target_text);
    void set_regex(std::string regex_text);
    void set_type(Type_flag type);
    void set_option(Option_flag option);
    void unset_option(Option_flag option);

    // Results
    Match get_match(std::size_t match_index) const;
    std::size_t match_count() const;

   private:
    // Data
    std::string target_text_;
    std::string regex_text_;
    Type_flag regex_type_;
    std::vector<Option_flag> regex_options_;

    // Results of Search
    std::vector<Match> matches_;

    // Performs Regex Search
    void update_results();
};

}  // namespace regex_explore
#endif  // REGEXPLORE_REGEX_STORE_HPP