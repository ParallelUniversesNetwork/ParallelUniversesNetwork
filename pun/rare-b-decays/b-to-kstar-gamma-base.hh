/* vim: set sw=4 sts=4 et foldmethod=syntax : */

#ifndef MASTER_GUARD_pun_RARE_B_DECAYS_B_TO_KSTAR_GAMMA_BASE_HH
#define MASTER_GUARD_pun_RARE_B_DECAYS_B_TO_KSTAR_GAMMA_BASE_HH 1

#include <pun/form-factors/mesonic.hh>
#include <pun/rare-b-decays/b-to-kstar-gamma.hh>
#include <pun/models/model.hh>
#include <pun/utils/options-impl.hh>

namespace pun
{
    class BToKstarGamma::AmplitudeGenerator :
        public ParameterUser
    {
        public:
            std::shared_ptr<Model> model;
            std::shared_ptr<FormFactors<PToV>> form_factors;

            UsedParameter hbar;

            UsedParameter mu;
            UsedParameter alpha_e;
            UsedParameter g_fermi;
            UsedParameter tau;

            UsedParameter m_B;
            UsedParameter m_Kstar;

            SwitchOption l;
            UsedParameter m_l;

            bool cp_conjugate;
            char q;
            double e_q;

            AmplitudeGenerator(const Parameters &, const Options &);

            virtual ~AmplitudeGenerator();
            virtual BToKstarGamma::Amplitudes amplitudes() const = 0;
    };

    template <typename Tag_> class BToKstarGammaAmplitudes;

    namespace tag
    {
        struct BFS2004;
    }
}

#endif
