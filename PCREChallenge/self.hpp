#ifndef INTERVIEW_SELF_HPP
#define INTERVIEW_SELF_HPP

#include <cassert>

template<typename T>
T& self(T* p) {
    assert(p);
    return *p;
}

#endif //INTERVIEW_SELF_HPP
