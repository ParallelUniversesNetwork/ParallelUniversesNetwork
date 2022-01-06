/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2017, 2019 Danny van Dyk
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

#include <pun/statistics/test-statistic.hh>
#include <pun/statistics/test-statistic-impl.hh>

namespace pun
{
    namespace test_statistics
    {
        Empty::Empty() = default;

        Empty::~Empty() = default;

        void
        Empty::output(std::ostream & stream) const
        {
            stream << "No test statistic available" << std::endl;
        }

        ChiSquare::ChiSquare(const double & chi2, const int & dof) :
            chi2(chi2),
            dof(dof)
        {
        }

        ChiSquare::~ChiSquare() = default;

        void
        ChiSquare::output(std::ostream & stream) const
        {
            stream << "chi^2 = " << chi2 << " with d.o.f. = " << dof << std::endl;
        }
    }
}
