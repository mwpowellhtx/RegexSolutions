#ifndef INTERVIEW_MATCH_FIXTURE_H
#define INTERVIEW_MATCH_FIXTURE_H

#include "await_results.h"
#include "report_results.h"
#include "options.h"

#include <mutex>

struct match_fixture {

    /// specifies what an is_match function should be about
    typedef std::function<bool(const std::string&, const std::string&)> is_match_func;

    /// specifies a verification function
    typedef std::function<void(matched_multimap::size_type, const matched_multimap& matches)> verify_func;

    /// ctor
    /// @param opt an options reference
    /// @param is_match an is match function
    /// @param verify a verification function
    match_fixture(
        options& opt
        , const is_match_func& is_match
        , const verify_func& verify
        = [](matched_multimap::size_type, const matched_multimap&) {});

    /// dtor
    virtual ~match_fixture();

    /// aggregates the lines from the known input stream
    /// @returns a reference to this instance
    match_fixture& aggregate();

    /// reports the results afterwards
    void report();

private:

    // for use when we emplace the matches
    typedef std::lock_guard<std::mutex> mutex_guard;

    /// convenience match function type definition
    /// @notes first arg is the line, second arg is the regex pattern
    typedef std::function<bool(std::string, std::string)> processor_func;

    /// processes the string line against the string regex pattern
    /// @param line a string line
    /// @param pattern a regex pattern
    /// @returns whether the line matched the pattern
    bool process(std::string line, std::string pattern);

private:

    options* _opt;

    /// mutex protecting the match emplacement
    std::mutex _mutex;

    /// verification function
    verify_func _verify;

    /// is match function
    is_match_func _is_match;

    /// deque keeping track of processing futures
    processing_deque _processing;

    /// matches to be emplaced here
    matched_multimap _matches;
};

#endif //INTERVIEW_MATCH_FIXTURE_H
