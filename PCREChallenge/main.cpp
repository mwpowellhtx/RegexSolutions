// facilitates the matching process
#include "match_fixture.h"

// incorporate loosely coupled matching solutions
#include "std_solution.h"
#include "pcre_solution.h"

#include <cassert>
#include <functional>

/// the main method
/// @param argc the number of args
/// @param argv the args themselves
int main(int argc, char* argv[]) {

    if (argc == 0) {
        return 1; //too few arguments
    }

    using std::placeholders::_1;
    using std::placeholders::_2;

    /* Considering the fact the regular expression patterns are virtually,
    if not precisely, identical, why not simply leverage std::regex, at
    minimum, or consider boost::regex is more precise features are required.
    See supporting commentary throughout the solution. */

    auto trx_is_match_ = std::bind(&trx::is_match, _1, _2);
    auto pcre_is_match_ = std::bind(&pcre_ns::is_match, _1, _2);

    /* demonstrated functionality in sub-blocks, followed by a closing "live"
    command line operation of the same */

    {
        test_options::pattern_vector patterns_;
        patterns_.push_back("\\D+\\d+.*");

        test_options opt_(
            "foo 154826 is a bar\n"
            "foo blah is bar\n"
            "foo blah\n"
            "foo 356824 is a very big boat\n"
            "foo blah is\n"
            , patterns_);

        match_fixture(opt_, pcre_is_match_
            , [](matched_multimap::size_type c, const matched_multimap& m) {

            assert(c == 2);
            assert(m.size() == c);
            assert(m.count("\\D+\\d+.*") == 2);
            assert(m.find("\\D+\\d+.*")->second == "foo 154826 is a bar");
            matched_multimap_range range_ = m.equal_range("\\D+\\d+.*");
            assert(count(range_) == 2);
            /* follow this: the first first is the equal range:
            the thing behind is is the actual pairing */
            auto current_ = range_.first;
            assert(current_->second == "foo 154826 is a bar");
            current_++;
            assert(current_->second == "foo 356824 is a very big boat");
        });
    }

    {
        //arrange for and run a demo involving std::regex features
        test_options::pattern_vector patterns_;
        patterns_.push_back("\\D+\\d+.*");

        test_options opt_(
            "this is a 1234 match\n"
            "this is a not a match\n"
            , patterns_);

        match_fixture(opt_, trx_is_match_
            , [](matched_multimap::size_type c, const matched_multimap& m) {
        
            assert(c == 1);
            assert(m.size() == c);
            assert(m.count("\\D+\\d+.*") == 1);
            assert(m.find("\\D+\\d+.*")->second == "this is a 1234 match");
        });
    }

    {
        // now go for the "live demo" after having run a couple of scenarios
        command_line_options opt(argc, argv);
        match_fixture(opt, opt.use_pcre() ? pcre_is_match_ : trx_is_match_);
    }

    return 0;
}
