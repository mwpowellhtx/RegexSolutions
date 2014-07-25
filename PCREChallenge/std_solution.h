#ifndef INTERVIEW_STD_SOLUTION_H
#define INTERVIEW_STD_SOLUTION_H

#include <string>

namespace trx {

    /// provides the focal point for matches
    /// @param l the string line being considered for match
    /// @param x a string pattern used to evaluate the line
    /// @returns whether the line matches the pattern regex
    /// @see http://www.cplusplus.com/reference/regex/
    /// @see http://www.cplusplus.com/reference/regex/regex_match/
    /// @see http://www.cplusplus.com/reference/regex/ECMAScript/
    bool is_match(const std::string& l, const std::string& x);
}

#endif //INTERVIEW_STD_SOLUTION_H
