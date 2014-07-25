#ifndef INTERVIEW_OPTIONS_H
#define INTERVIEW_OPTIONS_H

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>

/// options structure
/// @notes boost program_options is much stronger than any home spun options
struct options {

    /// going the extra mile: handle zero or more patterns
    typedef std::vector<std::string> pattern_vector;

    /// vector of patterns
    pattern_vector _patterns;

protected:

    /// default ctor
    options();

private:

    /// private copy ctor
    options(const options&);

public:

    /// dtor
    virtual ~options();

    /// returns either the opened stream or standard in
    /// @return either the opened stream or standard in
    virtual std::istream& stream() = 0;
};

struct test_options : options {

    /// ctor
    /// @param text a string test case
    /// @param patterns the patterns against which to match
    test_options(const std::string& text, const pattern_vector& patterns);

    /// dtor
    virtual ~test_options();

    /// returns either the opened stream or standard in
    /// @return either the opened stream or standard in
    virtual std::istream& stream() override;

private:

    /// a string test case
    std::string _text;

    /// a string stream ptr from which to read
    std::shared_ptr<std::stringstream> _ss;
};

struct command_line_options : options {

    /// ctor
    /// @param argc the number of input args
    /// @param argv the input args themselves
    command_line_options(int argc, char* argv[]);

    /// dtor
    virtual ~command_line_options();

    /// returns either the opened stream or standard in
    /// @return either the opened stream or standard in
    virtual std::istream& stream() override;

    /// returns whether to use PCRE
    /// @returns whether to use PCRE
    bool use_pcre();

private:

    /// whether to use PCRE
    bool _use_pcre;

    /// the filename of interest
    std::string _filename;

    /// an input stream ptr
    std::shared_ptr<std::ifstream> _ifs;

    /// returns whether the arg is the filename one
    /// @param arg the command line arg
    /// @returns whether is filename arg
    static bool is_filename_arg(const std::string& arg);

    /// returns whether the to use PCRE
    /// @param arg the command line arg
    /// @returns whether the to use PCRE
    static bool is_use_pcre(const std::string& arg);

    /// opens the filename if it were possible
    void open();
};

#endif //INTERVIEW_OPTIONS_H
