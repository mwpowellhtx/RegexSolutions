#include "std_solution.h"
#include "pcre_solution.h"
#include "options.h"

#include "await_results.h"
#include "report_results.h"

#include <cassert>
#include <functional>

/// convenience match function type definition
typedef std::function<bool(std::string, std::string)> processor_func;

/// the main method
/// @param argc the number of args
/// @param argv the args themselves
int main(int argc, char* argv[]) {

    if (argc == 0) {
        return 1; //too few arguments
    }

    // for use when we emplace the matches
    typedef std::lock_guard<std::mutex> mutex_guard;

    /// specifies what an is_match function should be about
    typedef std::function<bool(const std::string&, const std::string&)> is_match_func;

    // gather up the args and use them as match patterns
    options opt(argc, argv);

    // setup to do some match processing
    processing_deque processing;
    matched_multimap matches;
    std::mutex matches_mutex;

    using std::placeholders::_1;
    using std::placeholders::_2;

    //bind the match functionality one way or another
    //auto is_match = std::bind(&pcre_ns::is_match, _1, _2);
    auto is_match = std::bind(&trx::is_match, _1, _2);

    /*  for clarity not only that we receive the args but also returning bool,
    additionally capture the match details */
    processor_func process_match = [&is_match, &matches, &matches_mutex](
        std::string l, std::string x) -> bool {

        if (is_match(l, x)) {
            // guard the matches when we emplace them
            mutex_guard guard(matches_mutex);
            // mind the match emplacement: pattern followed by matching line
            matches.emplace(x, l);
            return true;
        }

        return false;
    };

    // receives input from the input stream
    auto aggregator = [&opt, &processing, &process_match](std::istream& is) {

        auto policy_ = std::launch::deferred;
        auto& patterns_ = opt._patterns;

        while (!is.eof()) {

            std::string line;

            std::getline(is, line);

            for (auto it = patterns_.begin(); it != patterns_.end(); it++) {
                processing.push_back(std::async(policy_, process_match, line, *it));
            }
        }
    };

    // aggregate from the options stream
    aggregator(opt.stream());

    // await the processing results
    auto count_ = await_results(processing);

    report_results(count_, matches);

    return 0;
}
