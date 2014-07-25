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

        // provides a workable regex solution using readily available resources
        std::regex e(x);

        /* the verbiage is similar but for some of the vocabulary:
        i.e. 'word for 'token', etc, etc. otherwise, a regex is a
        regex is a regex */
        return std::regex_match(l, e);
    }
}
