#include "pcre_solution.h"

#include <vector>
#include <cassert>

#include <pcre.h>

namespace pcre_ns {

    bool is_match(const std::string& l, const std::string& x) {

        /* observation: in how many lines of code here? as with any technical
        trade-off, do C-style things, expect C-style bugs. Like being more
        responsible over pointer, error code, or other safety. Not that we
        shouldn't, but one has to be more conscious of it here. */

        int ec;
        const char* err_msg;
        std::vector<int> offsets(20);
        const int compile_opt = 0;
        const int exec_opt = 0;

        /* Do as much as I can here to make things easier on myself and my
        colleagues. Still, there are more parameters to account for and
        potentially many more things that can fall sideways. */

        /* TODO: and if there isn't already an adapter, consider a C++ adapter
        to manage the PCRE lifetimes, compilation, exec, etc. */
        ::pcre* re = ::pcre_compile(
            x.c_str()
            , compile_opt
            , &err_msg
            , &ec
            , nullptr
            );

        //TODO: check error and/or free re prematurely
        assert(ec == 0);
        assert(re);

        ec = ::pcre_exec(
            re
            , nullptr
            , l.c_str()
            , l.length()
            , 0
            , exec_opt
            , offsets.data()
            , offsets.size()
            );

        ::pcre_free(re);

        ////TODO: may verify that the offsets seem reasonable
        //assert(ec > 0);

        /* returns negative error code (see docs),
        or a value somewhat contingent on the provided offsets. */
        return ec > 0;
    }
}
