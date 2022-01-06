/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2010, 2011, 2012, 2013, 2015, 2016 Danny van Dyk
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
 * You should have pun a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MASTER_GUARD_pun_RARE_B_DECAYS_B_TO_K_LL_BASE_HH
#define MASTER_GUARD_pun_RARE_B_DECAYS_B_TO_K_LL_BASE_HH 1

#include <pun/form-factors/mesonic.hh>
#include <pun/models/model.hh>
#include <pun/rare-b-decays/b-to-k-ll.hh>
#include <pun/utils/options-impl.hh>

namespace pun
{
    class BToKDilepton::AmplitudeGenerator :
        public ParameterUser
    {
        public:
            std::shared_ptr<Model> model;
            std::shared_ptr<FormFactors<PToP>> form_factors;
            SwitchOption opt_l;

            UsedParameter mu;
            UsedParameter alpha_e;
            UsedParameter g_fermi;
            UsedParameter tau;

            UsedParameter m_B;
            UsedParameter m_K;
            UsedParameter m_l;

            bool cp_conjugate;
            std::string lepton_flavor;

            AmplitudeGenerator(const Parameters &, const Options &);

            double beta_l(const double & q2) const;
            double energy(const double & q2) const;
            double lambda(const double & q2) const;
            double xi_pseudo(const double & q2) const;
            double normalisation(const double & q2) const;

            virtual ~AmplitudeGenerator();
            virtual BToKDilepton::Amplitudes amplitudes(const double & q2) const = 0;
    };

    struct BToKDilepton::DipoleFormFactors
    {
        complex<double> calT;
    };

    template <typename Tag_> class BToKDileptonAmplitudes;

    namespace tag
    {
        /*
         * Approaches that work at small q^2, or large recoil.
         */
        struct BFS2004;
        struct GvDV2020;

        /*
         * Approaches that work at large q^2, or low recoil.
         */
        struct GP2004;
    }
}

#endif
