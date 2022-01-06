/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2015, 2016 Danny van Dyk
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

#ifndef pun_GUARD_pun_B_DECAYS_B_TO_D_L_X_NU_HH
#define pun_GUARD_pun_B_DECAYS_B_TO_D_L_X_NU_HH 1

#include <pun/utils/options.hh>
#include <pun/utils/parameters.hh>
#include <pun/utils/private_implementation_pattern.hh>
#include <pun/utils/reference-name.hh>

namespace pun
{
    /*
     * Decay: B -> D l X_nu
     */
    class BToDLeptonInclusiveNeutrinos :
        public ParameterUser,
        public PrivateImplementationPattern<BToDLeptonInclusiveNeutrinos>
    {
        public:
            BToDLeptonInclusiveNeutrinos(const Parameters & parameters, const Options & options);
            ~BToDLeptonInclusiveNeutrinos();

            double differential_decay_width_1nu(const double & s, const double & c_theta_tau) const;

            double differential_decay_width_3nu(const double & s, const double & snunubar,
                    const double & c_theta_tau, const double & phi, const double & c_theta_mu_star) const;

            double integrated_decay_width_1nu(const double & s_min, const double & s_max) const;

            double integrated_decay_width_3nu(const double & s_min, const double & s_max) const;


            /*!
             * Descriptions of the process and its kinematics.
             */
            static const std::string description;
            static const std::string kinematics_description_s;
            static const std::string kinematics_description_snunubar;
            static const std::string kinematics_description_c_theta;
            static const std::string kinematics_description_c_theta_tau;
            static const std::string kinematics_description_c_theta_mu_star;
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
