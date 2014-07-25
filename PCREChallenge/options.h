#ifndef INTERVIEW_OPTIONS_H
#define INTERVIEW_OPTIONS_H

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>

/// options structure
/// @notes boost program_options is much stronger than any home spun options
struct options {

    /// going the extra mile: handle zero or more patterns
    typedef std::vector<std::string> pattern_vector;

    /// the filename of interest
    std::string _filename;

    /// vector of patterns
    pattern_vector _patterns;

private:

    /// an input stream ptr
    std::shared_ptr<std::ifstream> _s;

    /// opens the filename if it were possible
    void open();

    /// returns whether the arg is the filename one
    /// @param arg the command line arg
    /// @returns whether is filename arg
    static bool is_filename_arg(const std::string& arg);

public:

    /// ctor
    /// @param argc the number of input args
    /// @param argv the input args themselves
    options(int argc, char* argv[]);

    /// dtor
    virtual ~options();

public:

    /// returns either the opened stream or standard in
    /// @return either the opened stream or standard in
    std::istream& stream();
};

#endif //INTERVIEW_OPTIONS_H
