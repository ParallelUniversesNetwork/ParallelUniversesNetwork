/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2013, 2014, 2015 Danny van Dyk
 *
 * This file is part of the pun project. pun is free software;
 * you can redistribute it and/or modify it under the terms of the GNU General
 * Public License version 2, as published by the Free Software Foundation.
 *
 * pun is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef pun_GUARD_SRC_FORM_FACTORS_FORM_FACTORS_HH
#define pun_GUARD_SRC_FORM_FACTORS_FORM_FACTORS_HH 1

#include <pun/form-factors/baryonic.hh>
#include <pun/form-factors/mesonic.hh>
#include <pun/utils/exception.hh>

namespace pun
{
    class NoSuchFormFactorError :
        public Exception
    {
        public:
            NoSuchFormFactorError(const std::string & process, const std::string & tag);
    };
}

#endif
