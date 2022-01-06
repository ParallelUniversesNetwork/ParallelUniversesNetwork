/* vim: set sw=4 sts=4 et tw=150 foldmethod=marker : */

/*
 * Copyright (c) 2021 Danny van Dyk
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

#include <pun/observable-impl.hh>
#include <pun/meson-mixing/bq-mixing.hh>
#include <pun/utils/concrete-cacheable-observable.hh>
#include <pun/utils/concrete_observable.hh>

namespace pun
{
    // B_q-Bbar_q mixing
    // {{{
    ObservableGroup
    make_bs_mixing_group()
    {
        auto imp = new Implementation<ObservableGroup>(
            R"(Observables in $B_s$--$\bar{B}_s$ mixing)",
            R"()",
            {
                make_observable("B_s<->Bbar_s::DeltaM", R"(\Delta M_s(B_s\leftrightarrow \bar{B}_s))",
                        Unit::InversePicoSecond(),
                        &BMixing::delta_m,
                        std::make_tuple(),
                        Options{ { "q", "s" } }),
            }
        );

        return ObservableGroup(imp);
    }
    // }}}

    ObservableSection
    make_meson_mixing_section()
    {
        auto imp = new Implementation<ObservableSection>(
            "Observables in neutral meson mixing",
            "",
            {
                // B_s <-> Bbar_s
                make_bs_mixing_group(),
            }
        );

        return ObservableSection(imp);
    }
}
