/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2021 Danny van Dyk
 *
 * This file is part of the EOS project. EOS is free software;
 * you can redistribute it and/or modify it under the terms of the GNU General
 * Public License version 2, as published by the Free Software Foundation.
 *
 * EOS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <eos/utils/quantum-numbers.hh>

#include <array>

namespace eos
{
    std::ostream &
    operator<< (std::ostream & os, LeptonFlavor lf)
    {
        static const std::array<std::string, 3u> names
        {
            "e", "mu", "tau"
        };

        os << names[static_cast<unsigned>(lf)];

        return os;
    }

    std::ostream &
    operator<< (std::ostream & os, QuarkFlavor qf)
    {
        static const std::array<std::string, 6u> names
        {
            "u", "d", "s", "c", "b", "t"
        };

        os << names[static_cast<unsigned>(qf)];

        return os;
    }
}
