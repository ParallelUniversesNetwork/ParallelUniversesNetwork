/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2010, 2013, 2014, 2015, 2016 Danny van Dyk
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

#ifndef pun_GUARD_pun_DECAYS_HH
#define pun_GUARD_pun_DECAYS_HH 1

namespace pun
{
    /*
     * Phase space tags
     */
    struct LargeRecoil { };
    struct LowRecoil { };

    /*
     * B_s Decays
     */
    class BsToKstarLeptonNeutrino;

    /*
     * Rare B Decays
     */
    class BToKstarDilepton;

    class BsToPhiDilepton;

    class BToKDilepton;

    template <typename T_> class BToXsDilepton;

    template <typename T_> class BToXsGamma;

    template <typename T_> class LambdaBToLambdaDilepton;

    enum Helicity
    {
        left_handed = -1,
        right_handed = +1
    };
}

#endif
