/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2010, 2011, 2012, 2013, 2014, 2015, 2016 Danny van Dyk
 * Copyright (c) 2010, 2011 Christian Wacker
 * Copyright (c) 2014 Frederik Beaujean
 * Copyright (c) 2014 Christoph Bobeth
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

#ifndef MASTER_GUARD_pun_RARE_B_DECAYS_B_TO_K_LL_GP2004_HH
#define MASTER_GUARD_pun_RARE_B_DECAYS_B_TO_K_LL_GP2004_HH 1

#include <pun/rare-b-decays/b-to-k-ll-base.hh>

namespace pun
{
    template <>
    class BToKDileptonAmplitudes<tag::GP2004> :
        public BToKDilepton::AmplitudeGenerator
    {
        public:
            UsedParameter hbar;

            UsedParameter m_b_MSbar;
            UsedParameter m_c_MSbar;
            UsedParameter m_s;

            UsedParameter lambda_psd;
            UsedParameter sl_phase_psd;

            bool ccbar_resonance;

            bool use_nlo;

            BToKDileptonAmplitudes(const Parameters & p, const Options & o);
            ~BToKDileptonAmplitudes();

            virtual BToKDilepton::Amplitudes amplitudes(const double & q2) const;

            inline complex<double> c7eff(const WilsonCoefficients<BToS> & wc, const double & q2) const;
            inline complex<double> c9eff(const WilsonCoefficients<BToS> & wc, const double & q2) const;

            inline double m_b_PS() const;
            inline double kappa() const;
    };
}

#endif