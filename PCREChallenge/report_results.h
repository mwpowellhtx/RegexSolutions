#ifndef INTERVIEW_REPORT_RESULTS_H
#define INTERVIEW_REPORT_RESULTS_H

#include "await_results.h"

/// reports the matched patterns
/// @param count the overall count of matches
/// @param matches the matches themselves
void report_results(matched_multimap::size_type count, const matched_multimap& matches);

#endif //INTERVIEW_REPORT_RESULTS_H
