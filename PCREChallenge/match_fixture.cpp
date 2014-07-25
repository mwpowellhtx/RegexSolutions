#include "match_fixture.h"

#include <functional>
#include <algorithm>

#include "self.hpp"

match_fixture::match_fixture(
    options& opt
    , const is_match_func& is_match
    , const verify_func& verify)
    : _opt(&opt)
    , _mutex()
    , _verify(verify)
    , _is_match(is_match)
    , _processing()
    , _matches() {
}

match_fixture::~match_fixture() {
    aggregate().report();
}

bool match_fixture::process(std::string l, std::string x) {

    bool matched_ = _is_match(l, x);

    if (matched_) {

        // guard the matches when we emplace them
        mutex_guard guard(_mutex);

        // mind the match emplacement: pattern followed by matching line
        _matches.emplace(x, l);
    }

    return matched_;
}

match_fixture& match_fixture::aggregate() {

    using std::placeholders::_1;
    using std::placeholders::_2;

    auto policy_ = std::launch::deferred;
    auto& patterns_ = _opt->_patterns;
    auto& is_ = _opt->stream();

    // bind this guy one time since that can be an expensive repetitive prospect
    auto process_ = std::bind(&match_fixture::process, this, _1, _2);

    // ditto new line character trolling
    while (!is_.eof()) {

        std::string line;

        /* no need to go trolling for new line characters:
        http://www.cplusplus.com/reference/string/string/getline/ */
        std::getline(is_, line);

        std::for_each(patterns_.begin(), patterns_.end(), [&](const std::string& x) {
            _processing.push_back(std::async(policy_, process_, line, x));
        });
    }

    return self(this);
}

void match_fixture::report() {

    auto count_ = await_results(_processing);

    report_results(count_, _matches);

    _verify(count_, _matches);
}
