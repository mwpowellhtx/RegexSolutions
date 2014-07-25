#include "options.h"

#include <regex>

void options::open() {

    //TODO: might wait for the file to become available, etc
    const auto mode = std::ios_base::in;

    // if we could open the file then proceed
    if (std::ifstream(_filename, mode)) {
        _s = std::make_shared<std::ifstream>(_filename, mode);
    }
}

bool options::is_filename_arg(const std::string& arg) {
    return std::regex_match(arg, std::regex("[-/]f"));
}

options::options(int argc, char* argv[])
    : _filename(), _patterns(), _s() {

    // iterate through each of the args ignoring the first one (program path)
    for (int i = 1; i < argc; i++) {

        if (is_filename_arg(argv[i])) {
            //TODO: might be an exception otherwise
            if (i == argc - 1) return;
            _filename = argv[++i];
            continue;
        }

        // otherwise consider every other argument a potential pattern to match
        _patterns.push_back(argv[i]);
    }

    open();
}

options::~options() {
    // clean up after ourselves
    if (_s) {
        _s->close();
        _s.reset();
    }
}

std::istream& options::stream() {
    return _s ? *_s : std::cin;
}
