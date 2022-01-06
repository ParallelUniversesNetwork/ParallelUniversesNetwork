/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2021 Méril Reboud
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

#ifndef MASTER_GUARD_pun_RARE_B_DECAYS_BS_TO_PHI_LL_GVDV2020_HH
#define MASTER_GUARD_pun_RARE_B_DECAYS_BS_TO_PHI_LL_GVDV2020_HH 1

#include <pun/rare-b-decays/bs-to-phi-ll-base.hh>
#include <pun/rare-b-decays/nonlocal-formfactors.hh>
#include <pun/utils/options-impl.hh>

namespace pun
{
    template <>
    class BsToPhiDileptonAmplitudes<tag::GvDV2020> :
        public BsToPhiDilepton::AmplitudeGenerator
    {
        public:
            UsedParameter hbar;

            UsedParameter m_b_MSbar;
            UsedParameter m_s_MSbar;

            UsedParameter alpha_e;
            UsedParameter g_fermi;
            UsedParameter tau;

            SwitchOption opt_nonlocal_formfactor;
            NonlocalFormFactorPtr<nff::PToV> nonlocal_formfactor;

            BsToPhiDileptonAmplitudes(const Parameters & p, const Options & o);
            ~BsToPhiDileptonAmplitudes() = default;

            virtual BsToPhiDilepton::Amplitudes amplitudes(const double & q2) const;
    };
}

#endif
