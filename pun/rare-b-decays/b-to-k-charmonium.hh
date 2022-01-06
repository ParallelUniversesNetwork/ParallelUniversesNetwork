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

#ifndef pun_GUARD_pun_RARE_B_DECAYS_B_TO_K_CHARMONIUM_HH
#define pun_GUARD_pun_RARE_B_DECAYS_B_TO_K_CHARMONIUM_HH 1

#include <pun/maths/complex.hh>
#include <pun/utils/options.hh>
#include <pun/utils/parameters.hh>
#include <pun/utils/private_implementation_pattern.hh>
#include <pun/utils/reference-name.hh>

namespace pun
{
    /**
     * Decay: B -> K psi
     * with psi a narrow charmonium: psi = { J/psi, psi(2S) }
     */
    class BToKCharmonium :
        public ParameterUser,
        public PrivateImplementationPattern<BToKCharmonium>
    {
        public:
            ///@name Basic operations.
            ///@{

            BToKCharmonium(const Parameters & parameters, const Options & options);
            ~BToKCharmonium();

            ///@}

            ///@name Observables
            ///@{

            /// Branching ratio
            double branching_ratio() const;

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
