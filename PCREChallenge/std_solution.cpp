#include "std_solution.h"

#include <regex>

namespace trx {

    /// provides the focal point for matches
    /// @param l the string line being considered for match
    /// @param x a string pattern used to evaluate the line
    /// @returns whether the line matches the pattern regex
    /// @see http://www.cplusplus.com/reference/regex/
    /// @see http://www.cplusplus.com/reference/regex/regex_match/
    /// @see http://www.cplusplus.com/reference/regex/ECMAScript/
    bool is_match(const std::string& l, const std::string& x) {

        /* Contrast this from the PCRE-based solution. You can still mess
        this one up with badly formed regular expression patterns, and things
        of this nature. Besides that, there are not many ways to get this wrong,
        unless you are paying absolutely zero attention to it. The only potential
        snafu to consider is migrating from *Perl* Compatible Regular Expressions. */

        /* the verbiage is similar but for some of the vocabulary: i.e. 'word
        for 'token', etc, etc. otherwise, a regex is a regex is a regex */

        return std::regex_match(l, std::regex(x));
    }
}
