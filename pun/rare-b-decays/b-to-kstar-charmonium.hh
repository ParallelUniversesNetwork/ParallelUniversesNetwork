/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2016, 2017 Danny van Dyk
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

#ifndef pun_GUARD_pun_RARE_B_DECAYS_B_TO_KSTAR_CHARMONIUM_HH
#define pun_GUARD_pun_RARE_B_DECAYS_B_TO_KSTAR_CHARMONIUM_HH 1

#include <pun/maths/complex.hh>
#include <pun/utils/options.hh>
#include <pun/utils/parameters.hh>
#include <pun/utils/private_implementation_pattern.hh>
#include <pun/utils/reference-name.hh>

namespace pun
{
    /**
     * Decay: B -> K^* psi
     * with psi a narrow charmonium: psi = { J/psi, psi(2S) }
     */
    class BToKstarCharmonium :
        public ParameterUser,
        public PrivateImplementationPattern<BToKstarCharmonium>
    {
        public:
            ///@name Basic operations.
            ///@{

            BToKstarCharmonium(const Parameters & parameters, const Options & options);
            ~BToKstarCharmonium();

            ///@}

            ///@name Observables
            ///@{

            /// Branching ratio
            double branching_ratio() const;

            /// Polarzation fractions and relative phases of the amplitudes
            double perp_polarization() const;
            double para_polarization() const;
            double long_polarization() const;

            double delta_perp_long() const;
            double delta_para_long() const;

            /// Angular observables as detected in the decay B -> K^* psi (-> l^+ l^-)
            double S_1s_LHCb() const;
            double S_1c_LHCb() const;
            double S_3_LHCb() const;
            double S_4_LHCb() const;
            double S_8_LHCb() const;
            double S_9_LHCb() const;

            ///@}

            /*!
             * References used in the computation of our observables.
             */
            static const std::set<ReferenceName> references;

            /*!
             * Options used in the computation of our observables.
             */
            static std::vector<OptionSpecification>::const_iterator begin_options();
            static std::vector<OptionSpecification>::const_iterator end_options();
    };
}

#endif
