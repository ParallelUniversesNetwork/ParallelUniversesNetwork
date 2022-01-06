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

#ifndef MASTER_GUARD_pun_RARE_B_DECAYS_BS_TO_PHI_LL_BASE_HH
#define MASTER_GUARD_pun_RARE_B_DECAYS_BS_TO_PHI_LL_BASE_HH 1

#include <pun/form-factors/mesonic.hh>
#include <pun/models/model.hh>
#include <pun/rare-b-decays/bs-to-phi-ll.hh>
#include <pun/utils/options-impl.hh>

namespace pun
{
    class BsToPhiDilepton::AmplitudeGenerator :
        public ParameterUser
    {
        public:
            std::shared_ptr<Model> model;
            std::shared_ptr<FormFactors<PToV>> form_factors;
            SwitchOption opt_l;

            UsedParameter mu;
            UsedParameter alpha_e;
            UsedParameter g_fermi;
            UsedParameter tau;

            UsedParameter m_B;
            UsedParameter m_V;
            UsedParameter m_l;

            bool cp_conjugate;
            std::string lepton_flavor;

            AmplitudeGenerator(const Parameters &, const Options &);

            double s_hat(const double & q2) const;
            double beta_l(const double & q2) const;
            double energy(const double & q2) const;
            double lambda(const double & q2) const;

            virtual ~AmplitudeGenerator();
            virtual BsToPhiDilepton::Amplitudes amplitudes(const double & q2) const = 0;
    };

    struct BsToPhiDilepton::DipoleFormFactors
    {
        complex<double> calT_perp_left;
        complex<double> calT_perp_right;
        complex<double> calT_parallel;
    };

    template <typename Tag_> class BsToPhiDileptonAmplitudes;

    namespace tag
    {
        /*
         * Approaches that work at small q^2, or large recoil.
         */
        //struct BFS2004;
        struct GvDV2020;

        /*
         * Approaches that work at large q^2, or low recoil.
         */
        //struct GP2004;
    }
}

#endif
