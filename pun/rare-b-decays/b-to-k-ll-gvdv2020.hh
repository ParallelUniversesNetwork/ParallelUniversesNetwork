/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2020 Danny van Dyk
 * Copyright (c) 2011 Christian Wacker
 * Copyright (c) 2014 Frederik Beaujean
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

#ifndef MASTER_GUARD_pun_RARE_B_DECAYS_B_TO_K_LL_GVDV2020_HH
#define MASTER_GUARD_pun_RARE_B_DECAYS_B_TO_K_LL_GVDV2020_HH 1

#include <pun/rare-b-decays/b-to-k-ll-base.hh>
#include <pun/rare-b-decays/nonlocal-formfactors.hh>
#include <pun/rare-b-decays/qcdf-integrals.hh>
#include <pun/utils/options-impl.hh>

namespace pun
{
    template <>
    class BToKDileptonAmplitudes<tag::GvDV2020> :
        public BToKDilepton::AmplitudeGenerator
    {
        public:
            UsedParameter m_b_MSbar;
            UsedParameter m_c;
            UsedParameter m_s_MSbar;

            UsedParameter f_B;
            UsedParameter f_K;
            UsedParameter lambda_B_p_inv;
            UsedParameter a_1;
            UsedParameter a_2;

            UsedParameter lambda_psd;
            UsedParameter sl_phase_psd;

            SwitchOption opt_nonlocal_formfactor;
            NonlocalFormFactorPtr<nff::PToP> nonlocal_formfactor;

            double e_q;

            char q;

            std::function<QCDFIntegrals<BToKstarDilepton> (const double &, const double &,
                    const double &, const double &, const double &, const double &,
                    const double &, const double &)> qcdf_dilepton_massless_case;
            std::function<QCDFIntegrals<BToKstarDilepton> (const double &, const double &,
                    const double &, const double &, const double &, const double &,
                    const double &, const double &, const double &)> qcdf_dilepton_charm_case;
            std::function<QCDFIntegrals<BToKstarDilepton> (const double &, const double &,
                    const double &, const double &, const double &, const double &,
                    const double &, const double &, const double &)> qcdf_dilepton_bottom_case;

            BToKDileptonAmplitudes(const Parameters & p, const Options & o);
            ~BToKDileptonAmplitudes();

            virtual BToKDilepton::Amplitudes amplitudes(const double & q2) const;

            double m_b_PS() const;
            double mu_f() const;
            BToKDilepton::DipoleFormFactors dipole_form_factors(const double & q2, const WilsonCoefficients<BToS> & wc) const;
            double xi_pseudo(const double & q2) const;
    };
}

#endif
