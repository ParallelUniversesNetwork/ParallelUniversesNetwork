/* vim: set sw=4 sts=4 et foldmethod=syntax : */

#ifndef pun_GUARD_pun_MATHS_POLYLOG_HH
#define pun_GUARD_pun_MATHS_POLYLOG_HH 1

#include <pun/maths/complex.hh>

namespace pun
{
    complex<double> dilog(const complex<double> & z) __attribute__ ((pure));

    complex<double> trilog(const complex<double> & z) __attribute__ ((pure));
}

#endif
