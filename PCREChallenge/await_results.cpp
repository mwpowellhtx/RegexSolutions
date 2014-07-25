#include "await_results.h"

matched_multimap::size_type count(const matched_multimap_const_range& range) {

    matched_multimap::size_type count_ = 0;

    for (auto it = range.first; it != range.second; it++)
        count_++;

    return count_;
}

/// awaits each of the processing futures and tallies the overall result
/// @param processing a deque of matching futures
/// @returns the overall number of matches processed
matched_multimap::size_type await_results(processing_deque& processing) {

    matched_multimap::size_type count_ = 0;

    //enter something like a boost::wait_for_all for higher level functionality
    while (processing.size()) {

        auto& next_ = processing.front();

        bool got_ = next_.get();

        if (got_) {
            count_++;
        }

        processing.pop_front();
    }

    return count_;
}
