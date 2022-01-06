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

#ifndef MASTER_GUARD_pun_RARE_B_DECAYS_B_TO_KSTAR_LL_GVDV2020_HH
#define MASTER_GUARD_pun_RARE_B_DECAYS_B_TO_KSTAR_LL_GVDV2020_HH 1

#include <pun/rare-b-decays/b-to-kstar-ll-base.hh>
#include <pun/rare-b-decays/nonlocal-formfactors.hh>
#include <pun/utils/options-impl.hh>

namespace pun
{
    template <>
    class BToKstarDileptonAmplitudes<tag::GvDV2020> :
        public BToKstarDilepton::AmplitudeGenerator
    {
        public:
            UsedParameter hbar;

            UsedParameter m_b_MSbar;
            UsedParameter m_s_MSbar;

            UsedParameter alpha_e;
            UsedParameter g_fermi;
            UsedParameter tau;

            SwitchOption q;

            SwitchOption opt_nonlocal_formfactor;
            NonlocalFormFactorPtr<nff::PToV> nonlocal_formfactor;

            BToKstarDileptonAmplitudes(const Parameters & p, const Options & o);
            ~BToKstarDileptonAmplitudes() = default;

            virtual BToKstarDilepton::Amplitudes amplitudes(const double & q2) const;
    };
}

#endif
