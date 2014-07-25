#ifndef INTERVIEW_AWAIT_RESULTS_H
#define INTERVIEW_AWAIT_RESULTS_H

#include <future>
#include <deque>
#include <map>

/// one of my favorite data structures the double ended queue (pronouced "deck")
typedef std::deque<std::future<bool>> processing_deque;

/// another favorite data structure not far behind deque when multiple matched patterns could occur
/// @notes should emplace the pattern followed by the matching line
typedef std::multimap<std::string, std::string> matched_multimap;

/// convenience multimap range type definition
typedef std::pair<
    matched_multimap::const_iterator
    , matched_multimap::const_iterator> matched_multimap_const_range;

/// awaits each of the processing futures and tallies the overall result
/// @param processing a deque of matching futures
/// @returns the overall number of matches processed
matched_multimap::size_type await_results(processing_deque& processing);

/// returns the number of elements in the multimap range
/// @params range a multimap range
/// @returns the number of elements in the multimap range
matched_multimap::size_type count(const matched_multimap_const_range& range);

#endif //INTERVIEW_AWAIT_RESULTS_H
