/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2014, 2015 Danny van Dyk
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

#ifndef pun_GUARD_pun_MODELS_CKM_HH
#define pun_GUARD_pun_MODELS_CKM_HH 1

#include <pun/models/model.hh>
#include <pun/models/standard-model.hh>

namespace pun
{
    class CKMScanComponent :
        public virtual ModelComponent<components::CKM>
    {
        private:
            /* CKM matrix elements */
            UsedParameter _v_ud_abs__ckm;
            UsedParameter _v_ud_arg__ckm;

            UsedParameter _v_us_abs__ckm;
            UsedParameter _v_us_arg__ckm;

            UsedParameter _v_ub_abs__ckm;
            UsedParameter _v_ub_arg__ckm;

            UsedParameter _v_cd_abs__ckm;
            UsedParameter _v_cd_arg__ckm;

            UsedParameter _v_cs_abs__ckm;
            UsedParameter _v_cs_arg__ckm;

            UsedParameter _v_cb_abs__ckm;
            UsedParameter _v_cb_arg__ckm;

            UsedParameter _v_td_abs__ckm;
            UsedParameter _v_td_arg__ckm;

            UsedParameter _v_ts_abs__ckm;
            UsedParameter _v_ts_arg__ckm;

            UsedParameter _v_tb_abs__ckm;
            UsedParameter _v_tb_arg__ckm;

        public:
            CKMScanComponent(const Parameters &, const Options &, ParameterUser &);

            /* CKM matrix elements */
            virtual complex<double> ckm_cd() const;
            virtual complex<double> ckm_cs() const;
            virtual complex<double> ckm_cb() const;
            virtual complex<double> ckm_ud() const;
            virtual complex<double> ckm_us() const;
            virtual complex<double> ckm_ub() const;
            virtual complex<double> ckm_td() const;
            virtual complex<double> ckm_ts() const;
            virtual complex<double> ckm_tb() const;
    };

    class CKMScanModel :
        public Model,
        public CKMScanComponent,
        public SMComponent<components::QCD>,
        public SMComponent<components::WET::SBSB>,
        public SMComponent<components::DeltaBS1>,
        public SMComponent<components::WET::UBLNu>,
        public SMComponent<components::WET::CBLNu>,
        public SMComponent<components::WET::SBNuNu>
    {
        public:
            CKMScanModel(const Parameters &, const Options &);
            virtual ~CKMScanModel();

            static std::shared_ptr<Model> make(const Parameters &, const Options &);
    };
}

#endif
