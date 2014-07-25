#include "options.h"

#include <regex>

///////////////////////////////////////////////////////////////////////////
options::options()
    : _patterns() {
}

options::options(const options&)
    : _patterns() {
}

options::~options() {
}

///////////////////////////////////////////////////////////////////////////
test_options::test_options(
    const std::string& text
    , const pattern_vector& patterns)
    : _text(text)
    , _ss(std::make_shared<std::stringstream>(_text)) {

    _patterns.insert(_patterns.end(), patterns.begin(), patterns.end());
}

test_options::~test_options() {
    if (_ss) {
        _ss.reset();
    }
}

std::istream& test_options::stream() {
    return *_ss;
}

///////////////////////////////////////////////////////////////////////////
command_line_options::command_line_options(int argc, char* argv[])
    : options()
    , _use_pcre(false)
    , _filename()
    , _ifs() {

    // iterate through each of the args ignoring the first one (program path)
    for (int i = 1; i < argc; i++) {

        if (is_use_pcre(argv[i])) {
            _use_pcre = true;
            continue;
        }

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

command_line_options::~command_line_options() {
    // clean up after ourselves
    if (_ifs) {
        _ifs->close();
        _ifs.reset();
    }
}

std::istream& command_line_options::stream() {
    return _ifs ? *_ifs : std::cin;
}

bool command_line_options::use_pcre() {
    return _use_pcre;
}

bool command_line_options::is_filename_arg(const std::string& arg) {
    return std::regex_match(arg, std::regex("[-/]f"));
}

bool command_line_options::is_use_pcre(const std::string& arg) {
    return std::regex_match(arg, std::regex("[-/]pcre"));
}

void command_line_options::open() {

    //TODO: might wait for the file to become available, etc
    const auto mode = std::ios_base::in;

    // if we could open the file then proceed
    if (std::ifstream(_filename, mode)) {
        _ifs = std::make_shared<std::ifstream>(_filename, mode);
    }
}
