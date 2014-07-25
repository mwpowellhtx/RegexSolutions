
8:55 AM 7/25/2014

pulled in the PCRE from its NuGet source
it seems PCRE was updated for Visual Studio 2012
it is simple enough to support this through Visual Studio 2013

initial impressions, PCRE may be overkill, and fitting a square peg through a round hole
at minimum an adapter pattern would be helpful to manage the PCRE lifetimes, etc
especially when you stop to consider the status of std::regex today

the examples enumerated in the docs were inaccurate at best
the implied claim was that perl-compatible regular expressions should be used
however, the examples do not refect perl regular expressions whatsoever
adjustments were made to work around this oversight

this is from a Windows platform, at any rate
analysis would be required on a Linux platform
