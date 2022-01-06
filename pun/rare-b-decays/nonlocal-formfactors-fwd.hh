/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2017-2020 Danny van Dyk
 * Copyright (c) 2019-2020 Nico Gubernari
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

#ifndef pun_GUARD_pun_RARE_B_DECAYS_NONLOCAL_FORMFACTORS_FWD_HH
#define pun_GUARD_pun_RARE_B_DECAYS_NONLOCAL_FORMFACTORS_FWD_HH 1

namespace pun
{
    namespace nff
    {
        // P -> P
        struct PToP { };

        // forward declarations
        struct BToK;

        // P -> V
        struct PToV { };

        // forward declarations
        struct BToKstar;
        struct BsToPhi;
    }
}

#endif
