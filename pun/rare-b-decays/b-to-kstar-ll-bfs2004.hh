/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2011 Christian Wacker
 * Copyright (c) 2014 Christoph Bobeth
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

#ifndef MASTER_GUARD_pun_RARE_B_DECAYS_B_TO_KSTAR_LL_BFS2004_HH
#define MASTER_GUARD_pun_RARE_B_DECAYS_B_TO_KSTAR_LL_BFS2004_HH 1

#include <pun/rare-b-decays/b-to-kstar-ll-base.hh>
#include <pun/rare-b-decays/qcdf-integrals.hh>

namespace pun
{
    template <>
    class BToKstarDileptonAmplitudes<tag::BFS2004> :
        public BToKstarDilepton::AmplitudeGenerator
    {
        public:
            UsedParameter hbar;

            UsedParameter m_b_MSbar;
            UsedParameter m_c;
            UsedParameter m_s_MSbar;

            UsedParameter f_B;
            UsedParameter f_Kstar_par;
            UsedParameter f_Kstar_perp;
            UsedParameter lambda_B_p_inv;
            UsedParameter a_1_par;
            UsedParameter a_2_par;
            UsedParameter a_1_perp;
            UsedParameter a_2_perp;

            UsedParameter uncertainty_para;
            UsedParameter uncertainty_perp;
            UsedParameter uncertainty_long;

            UsedParameter uncertainty_xi_perp;
            UsedParameter uncertainty_xi_par;

            double e_q;

            char q;

            bool ccbar_resonance;

            bool use_nlo;

            std::function<QCDFIntegrals<BToKstarDilepton> (const double &, const double &,
                    const double &, const double &, const double &, const double &,
                    const double &, const double &)> qcdf_dilepton_massless_case;
            std::function<QCDFIntegrals<BToKstarDilepton> (const double &, const double &,
                    const double &, const double &, const double &, const double &,
                    const double &, const double &, const double &)> qcdf_dilepton_charm_case;
            std::function<QCDFIntegrals<BToKstarDilepton> (const double &, const double &,
                    const double &, const double &, const double &, const double &,
                    const double &, const double &, const double &)> qcdf_dilepton_bottom_case;

            std::string ff_relation;

            BToKstarDileptonAmplitudes(const Parameters & p, const Options & o);
            ~BToKstarDileptonAmplitudes();

            virtual BToKstarDilepton::Amplitudes amplitudes(const double & q2) const;

            double m_b_PS() const;
            double mu_f() const;
            BToKstarDilepton::DipoleFormFactors dipole_form_factors(const double & q2, const WilsonCoefficients<BToS> & wc) const;
            double norm(const double & q2) const;
            double xi_perp(const double & q2) const;
            double xi_par(const double & q2) const;
    };
}

#endif
