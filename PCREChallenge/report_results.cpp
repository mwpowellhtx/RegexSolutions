#include "report_results.h"

#include <iostream>
#include <string>
#include <cassert>

void report_results(matched_multimap::size_type count, const matched_multimap& matches) {

    assert(count == matches.size());

    std::cout << "total matched: " << count << std::endl;

    matched_multimap::size_type sub_count_ = 0;
    std::shared_ptr<std::string> pattern;

    auto summarize = [](matched_multimap::size_type& c) {
        std::cout << "sub-total matched: " << c << std::endl;
        c = 0;
    };

    for (auto it = matches.cbegin(); it != matches.cend(); it++) {

        if (!pattern || *pattern != it->first) {

            if (pattern) summarize(sub_count_);

            pattern = std::make_shared<std::string>(it->first);

            std::cout << "matches for pattern: " << '"' << *pattern << '"' << std::endl;
        }

        std::cout << it->second << std::endl;
        sub_count_++;
    }

    summarize(sub_count_);

    std::cout << "press Enter to continue..." << std::endl;

    std::getchar();
}
