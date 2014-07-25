#ifndef INTERVIEW_PCRE_SOLUTION_H
#define INTERVIEW_PCRE_SOLUTION_H

#include <string>

namespace pcre_ns {

    /// provides the focal point for matches using pcre
    /// @param l the string line being considered for match
    /// @param x a string pattern used to evaluate the line
    /// @returns whether the line matches the pattern regex
    bool is_match(const std::string& l, const std::string& x);
}

#endif //INTERVIEW_PCRE_SOLUTION_H
