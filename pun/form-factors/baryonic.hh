/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2014, 2015, 2016 Danny van Dyk
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

#ifndef pun_GUARD_pun_FORM_FACTORS_BARYONIC_HH
#define pun_GUARD_pun_FORM_FACTORS_BARYONIC_HH 1

#include <pun/form-factors/form-factors-fwd.hh>
#include <pun/utils/diagnostics.hh>
#include <pun/utils/options.hh>
#include <pun/utils/parameters.hh>
#include <pun/utils/qualified-name.hh>

#include <map>
#include <memory>
#include <string>

namespace pun
{
    /* Baryonic Tags */

    /*
     * J=1/2^+ -> J=1/2^+ transitions
     */
    struct OneHalfPlusToOneHalfPlus { };

    /*
     * J=1/2^+ -> J=1/2^- transitions
     */
    struct OneHalfPlusToOneHalfMinus { };

    /*
     * J=1/2^+ -> J=3/2^- transitions
     */
    struct OneHalfPlusToThreeHalfMinus { };

    template <>
    class FormFactors<OneHalfPlusToOneHalfPlus> :
        public ParameterUser
    {
        public:
            virtual ~FormFactors();

            virtual double f_time_v(const double & s) const = 0;
            virtual double f_long_v(const double & s) const = 0;
            virtual double f_perp_v(const double & s) const = 0;

            virtual double f_time_a(const double & s) const = 0;
            virtual double f_long_a(const double & s) const = 0;
            virtual double f_perp_a(const double & s) const = 0;

            virtual double f_long_t(const double & s) const = 0;
            virtual double f_perp_t(const double & s) const = 0;

            virtual double f_long_t5(const double & s) const = 0;
            virtual double f_perp_t5(const double & s) const = 0;
    };

    template <>
    class FormFactorFactory<OneHalfPlusToOneHalfPlus>
    {
        public:
            using KeyType = QualifiedName;
            using ValueType = std::function<FormFactors<OneHalfPlusToOneHalfPlus> * (const Parameters &, const Options &)>;

            static const std::map<KeyType, ValueType> form_factors;

            static std::shared_ptr<FormFactors<OneHalfPlusToOneHalfPlus>> create(const QualifiedName & name, const Parameters & parameters, const Options & options = Options{ });
            static OptionSpecification option_specification(const qnp::Prefix & process);
    };

    template <>
    class FormFactors<OneHalfPlusToOneHalfMinus> :
        public ParameterUser
    {
        public:
            virtual ~FormFactors();

            virtual double f_time_v(const double & s) const = 0;
            virtual double f_long_v(const double & s) const = 0;
            virtual double f_perp_v(const double & s) const = 0;

            virtual double f_time_a(const double & s) const = 0;
            virtual double f_long_a(const double & s) const = 0;
            virtual double f_perp_a(const double & s) const = 0;

            virtual Diagnostics diagnostics() const;
    };

    template <>
    class FormFactorFactory<OneHalfPlusToOneHalfMinus>
    {
        public:
            using KeyType = QualifiedName;
            using ValueType = std::function<FormFactors<OneHalfPlusToOneHalfMinus> * (const Parameters &, const Options &)>;

            static const std::map<KeyType, ValueType> form_factors;

            static std::shared_ptr<FormFactors<OneHalfPlusToOneHalfMinus>> create(const QualifiedName & name, const Parameters & parameters, const Options & options = Options{ });
            static OptionSpecification option_specification(const qnp::Prefix & process);
    };

    template <>
    class FormFactors<OneHalfPlusToThreeHalfMinus> :
        public ParameterUser
    {
        public:
            virtual ~FormFactors();

            virtual double f_time12_v(const double & s) const = 0;
            virtual double f_long12_v(const double & s) const = 0;
            virtual double f_perp12_v(const double & s) const = 0;
            virtual double f_perp32_v(const double & s) const = 0;

            virtual double f_time12_a(const double & s) const = 0;
            virtual double f_long12_a(const double & s) const = 0;
            virtual double f_perp12_a(const double & s) const = 0;
            virtual double f_perp32_a(const double & s) const = 0;

            virtual Diagnostics diagnostics() const;
    };

    template <>
    class FormFactorFactory<OneHalfPlusToThreeHalfMinus>
    {
        public:
            using KeyType = QualifiedName;
            using ValueType = std::function<FormFactors<OneHalfPlusToThreeHalfMinus> * (const Parameters &, const Options &)>;

            static const std::map<KeyType, ValueType> form_factors;

            static std::shared_ptr<FormFactors<OneHalfPlusToThreeHalfMinus>> create(const QualifiedName & name, const Parameters & parameters, const Options & options = Options{ });
            static OptionSpecification option_specification(const qnp::Prefix & process);
    };
}

#endif
