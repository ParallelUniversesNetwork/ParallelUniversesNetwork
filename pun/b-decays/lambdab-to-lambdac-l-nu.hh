/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2019 Ahmet Kokulu
 * Copyright (c) 2019 Danny van Dyk
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

#ifndef pun_GUARD_pun_B_DECAYS_BARYONIC_B_TO_C_LEPTON_NEUTRINO_HH
#define pun_GUARD_pun_B_DECAYS_BARYONIC_B_TO_C_LEPTON_NEUTRINO_HH 1

#include <pun/rare-b-decays/decays.hh>
#include <pun/utils/options.hh>
#include <pun/utils/parameters.hh>
#include <pun/utils/private_implementation_pattern.hh>
#include <pun/utils/reference-name.hh>

namespace pun
{
    /*
     * Decay: Lambda_b -> Lambda_c lnu
     */
    class LambdaBToLambdaCLeptonNeutrino :
        public ParameterUser,
        public PrivateImplementationPattern<LambdaBToLambdaCLeptonNeutrino>
    {
        public:
            LambdaBToLambdaCLeptonNeutrino(const Parameters &, const Options &);
            ~LambdaBToLambdaCLeptonNeutrino();

            double four_differential_decay_width(const double & q2, const double & c_lep, const double & c_lam, const double & phi) const;
            double integrated_decay_width(const double & q2_min, const double & q2_max) const;

            double differential_branching_ratio(const double & q2) const;
            double differential_a_fb_leptonic(const double & q2) const;
            double differential_a_fb_hadronic(const double & q2) const;
            double differential_a_fb_combined(const double & q2) const;
            double differential_fzero(const double & q2) const;

            double integrated_branching_ratio(const double & q2_min, const double & q2_max) const;
            double integrated_a_fb_leptonic(const double & q2_min, const double & q2_max) const;
            double integrated_a_fb_hadronic(const double & q2_min, const double & q2_max) const;
            double integrated_a_fb_combined(const double & q2_min, const double & q2_max) const;
            double integrated_fzero(const double & q2_min, const double & q2_max) const;
            double integrated_k1ss(const double & q2_min, const double & q2_max) const;
            double integrated_k1cc(const double & q2_min, const double & q2_max) const;
            double integrated_k1c(const double & q2_min, const double & q2_max) const;
            double integrated_k2ss(const double & q2_min, const double & q2_max) const;
            double integrated_k2cc(const double & q2_min, const double & q2_max) const;
            double integrated_k2c(const double & q2_min, const double & q2_max) const;
            double integrated_k3sc(const double & q2_min, const double & q2_max) const;
            double integrated_k3s(const double & q2_min, const double & q2_max) const;
            double integrated_k4sc(const double & q2_min, const double & q2_max) const;
            double integrated_k4s(const double & q2_min, const double & q2_max) const;

            /*!
            * Descriptions of the process and its kinematics.
            */
            static const std::string description;
            static const std::string kinematics_description_q2;
            static const std::string kinematics_description_c_theta_l;
            static const std::string kinematics_description_c_theta_L;
            static const std::string kinematics_description_phi;

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
