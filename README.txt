
12:35 AM 7/25/2014

pulled in the PCRE from its NuGet source
it seems PCRE was updated for Visual Studio 2012
since I am using 2013, I "patched" the project file(s) to indicate v110 instead of v120
which permits the includes, libs, etc, to be resolved properly by the NuGet-delivered-targets

initial impressions, PCRE may be overkill, and fitting a square peg through a round hole
at minimum an adapter class would be helpful to manage the PCRE lifetimes, etc
especially when you stop to consider the status of std::regex today

the examples enumerated in the docs were inaccurate
they do not reflect perl regex at all
in fact, perl regex is closer to std::regex, or vice versa
which is another reason to seriously consider whether the state of std::regex doesn't fit the bill

this is from a Windows platform, at any rate
analysis would be required on a Linux platform
