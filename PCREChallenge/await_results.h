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

/// awaits each of the processing futures and tallies the overall result
/// @param processing a deque of matching futures
/// @returns the overall number of matches processed
matched_multimap::size_type await_results(processing_deque& processing);

#endif //INTERVIEW_AWAIT_RESULTS_H
