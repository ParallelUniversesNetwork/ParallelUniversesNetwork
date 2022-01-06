/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2015, 2017 Danny van Dyk
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

#ifndef pun_GUARD_pun_FORM_FACTORS_ZERO_RECOIL_SUM_RULE_HH
#define pun_GUARD_pun_FORM_FACTORS_ZERO_RECOIL_SUM_RULE_HH 1

#include <pun/utils/diagnostics.hh>
#include <pun/utils/parameters.hh>
#include <pun/utils/options.hh>
#include <pun/utils/reference-name.hh>

namespace pun
{
    template <typename Tag_> class ZeroRecoilSumRule;

    class LambdaBToC {};

    template <>
    class ZeroRecoilSumRule<LambdaBToC> :
        public ParameterUser,
        public PrivateImplementationPattern<ZeroRecoilSumRule<LambdaBToC>>
    {
        public:
            ZeroRecoilSumRule(const Parameters &, const Options &);

            ~ZeroRecoilSumRule();

            // inclusive bounds
            double vector_current() const;
            double axialvector_current() const;

            // inelastic contributions from orbitally excited doublet Lambda_c^*
            double vector_current_inel() const;
            double axialvector_current_inel() const;

            /* Diagnostics for unit tests */
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
