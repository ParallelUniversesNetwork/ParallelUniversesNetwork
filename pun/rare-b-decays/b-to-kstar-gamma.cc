/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2010, 2011, 2012, 2015, 2016 Danny van Dyk
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

#include <pun/models/model.hh>
#include <pun/rare-b-decays/b-to-kstar-gamma-base.hh>
#include <pun/rare-b-decays/b-to-kstar-gamma-bfs2004.hh>
#include <pun/utils/options.hh>
#include <pun/utils/options-impl.hh>
#include <pun/utils/private_implementation_pattern-impl.hh>

#include <cmath>

#include <gsl/gsl_sf.h>

namespace pun
{
    using namespace std::placeholders;
    using std::norm;

    /*!
     * Implementation for the decay @f$\bar{B} \to \bar{K}^* \gamma@f$.
     */
    template <>
    struct Implementation<BToKstarGamma>
    {
        std::shared_ptr<Model> model;

        UsedParameter hbar;

        SwitchOption q;

        UsedParameter tau;

        SwitchOption tag;

        std::shared_ptr<BToKstarGamma::AmplitudeGenerator> amplitude_generator;

        static const std::vector<OptionSpecification> options;

        Implementation(const Parameters & p, const Options & o, ParameterUser & u) :
            model(Model::make(o.get("model", "SM"), p, o)),
            hbar(p["QM::hbar"], u),
            q(o, "q", { "d", "u" }, "d"),
            tau(p["life_time::B_" + q.value()], u),
            tag(o, "tag", { "BFS2004"})
        {
            if ("BFS2004" == tag.value())
            {
                amplitude_generator.reset(new BToKstarGammaAmplitudes<tag::BFS2004>(p, o));
            }
            else
            {
                throw InternalError("BToKstarGamma: Unknown tag or no valid tag specified (tag = '" + tag.value() + "')!");
            }

            u.uses(*model);
            u.uses(*amplitude_generator);
        }

        double decay_rate()
        {
            auto amps = amplitude_generator->amplitudes();

            return std::norm(amps.a_perp) + std::norm(amps.a_para);
        }

        complex<double> q_over_p()
        {
            double phi_d = arg(pow(conj(model->ckm_td()) * model->ckm_tb(), 2));
            return std::polar(1.0, -phi_d);
        }

        complex<double> a_left()
        {
            BToKstarGamma::Amplitudes a = amplitude_generator->amplitudes();
            return (a.a_para + a.a_perp) / sqrt(2.0);;
        }

        complex<double> a_right()
        {
            BToKstarGamma::Amplitudes a = amplitude_generator->amplitudes();
            return (a.a_para - a.a_perp) / sqrt(2.0);;
        }
    };

    BToKstarGamma::BToKstarGamma(const Parameters & parameters, const Options & options) :
        PrivateImplementationPattern<BToKstarGamma>(new Implementation<BToKstarGamma>(parameters, options, *this))
    {
    }

    BToKstarGamma::~BToKstarGamma() = default;

    const std::vector<OptionSpecification>
    Implementation<BToKstarGamma>::options
    {
        {"q", { "d", "u" }, "d"}
    };

    double
    BToKstarGamma::decay_rate() const
    {
        return _imp->decay_rate();
    }

    double
    BToKstarGamma::branching_ratio() const
    {
        // cf. [PDG2008] : Gamma = hbar / tau_B, pp. 5, 79
        double Gamma_B = _imp->hbar() / _imp->tau;
        double gamma   = _imp->decay_rate();

        return gamma / Gamma_B;
    }

    double
    BToKstarGamma::real_q_over_p() const
    {
        return real(_imp->q_over_p());
    }

    double
    BToKstarGamma::imag_q_over_p() const
    {
        return imag(_imp->q_over_p());
    }

    double
    BToKstarGamma::real_a_left() const
    {
        return real(_imp->a_left());
    }

    double
    BToKstarGamma::imag_a_left() const
    {
        return imag(_imp->a_left());
    }

    double
    BToKstarGamma::real_a_right() const
    {
        return real(_imp->a_right());
    }

    double
    BToKstarGamma::imag_a_right() const
    {
        return imag(_imp->a_right());
    }

    const std::set<ReferenceName>
    BToKstarGamma::references
    {
    };

    std::vector<OptionSpecification>::const_iterator
    BToKstarGamma::begin_options()
    {
        return Implementation<BToKstarGamma>::options.cbegin();
    }

    std::vector<OptionSpecification>::const_iterator
    BToKstarGamma::end_options()
    {
        return Implementation<BToKstarGamma>::options.cend();
    }
}
