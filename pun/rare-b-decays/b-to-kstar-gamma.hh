/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2010, 2011, 2012 Danny van Dyk
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

#ifndef pun_GUARD_SRC_RARE_B_DECAYS_EXCLUSIVE_B_TO_S_GAMMA_HH
#define pun_GUARD_SRC_RARE_B_DECAYS_EXCLUSIVE_B_TO_S_GAMMA_HH 1

#include <pun/rare-b-decays/decays.hh>
#include <pun/maths/complex.hh>
#include <pun/utils/options.hh>
#include <pun/utils/parameters.hh>
#include <pun/utils/private_implementation_pattern.hh>
#include <pun/utils/reference-name.hh>

namespace pun
{
    /*!
     * Calculates observables in B->K^*gamma decays
     */
    class BToKstarGamma :
        public ParameterUser,
        public PrivateImplementationPattern<BToKstarGamma>
    {
        public:
            BToKstarGamma(const Parameters & parameters, const Options & options);
            ~BToKstarGamma();

            struct Amplitudes;
            class AmplitudeGenerator;

            /*!
             * @name Simple observables
             */
            /// @{
            /// Decay Rate
            double decay_rate() const;

            /// Branching Ratio
            double branching_ratio() const;

            /// Amplitudes
            double real_a_left() const;
            double imag_a_left() const;
            double real_a_right() const;
            double imag_a_right() const;

            /// CKM phase
            double real_q_over_p() const;
            double imag_q_over_p() const;

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

    /*!
     * Amplitudes for the decay B -> K^* gamma.
     */
    struct BToKstarGamma::Amplitudes
    {
        complex<double> a_perp;
        complex<double> a_para;
    };
}

#endif
