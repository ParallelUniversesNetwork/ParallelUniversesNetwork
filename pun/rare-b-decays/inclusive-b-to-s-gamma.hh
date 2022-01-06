/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2010, 2011, 2012, 2013 Danny van Dyk
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

#ifndef pun_GUARD_SRC_RARE_B_DECAYS_INCLUSIVE_B_TO_S_GAMMA_HH
#define pun_GUARD_SRC_RARE_B_DECAYS_INCLUSIVE_B_TO_S_GAMMA_HH 1

#include <pun/rare-b-decays/decays.hh>
#include <pun/maths/complex.hh>
#include <pun/utils/diagnostics.hh>
#include <pun/utils/options.hh>
#include <pun/utils/parameters.hh>
#include <pun/utils/private_implementation_pattern.hh>
#include <pun/utils/reference-name.hh>

namespace pun
{
    /*
     * Decay: b -> X_s gamma
     */

    // LO-NP Enhancement of [2006zs]
    struct Minimal
    {
    };

    template <>
    class BToXsGamma<Minimal> :
        public ParameterUser,
        public PrivateImplementationPattern<BToXsGamma<Minimal>>
    {
        public:
            BToXsGamma(const Parameters & parameters, const Options & options);
            ~BToXsGamma();

            // Integrated Observables
            double integrated_branching_ratio() const;

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

    // NLO Implementation
    struct NLO
    {
    };

    template <>
    class BToXsGamma<NLO> :
        public ParameterUser,
        public PrivateImplementationPattern<BToXsGamma<NLO>>
    {
        public:
            BToXsGamma(const Parameters & parameters, const Options & options);
            ~BToXsGamma();

            // Branching ratio
            double integrated_branching_ratio(const double & emin) const;

            // Photon energy moments
            double photon_energy_moment_1(const double & emin) const;
            double photon_energy_moment_2(const double & emin) const;

            // Diagnostics
            Diagnostics diagnostics() const;

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
