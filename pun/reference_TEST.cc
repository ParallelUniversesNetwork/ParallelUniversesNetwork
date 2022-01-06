/* vim: set sw=4 sts=4 et foldmethod=marker foldmarker={{{,}}} : */

/*
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

#include <test/test.hh>
#include <pun/reference.hh>

#include <vector>

using namespace test;
using namespace pun;

class ReferencesTest :
    public TestCase
{
    public:
        ReferencesTest() :
            TestCase("references_test")
        {
        }

        virtual void run() const
        {
            /* Test iterating over references */
            {
                std::cout << "# References :" << std::endl;

                auto references = References();
                unsigned n = 0;

                for (const auto & r : references)
                {
                    std::cout << "#  " << r.first.str() << ": ";
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }

            /* Test retrieving Reference by name */
            {
                auto references = References();

                static const std::vector<ReferenceName> names
                {
                    "ATLAS:2013A",
                    "BHvD:2012A"
                };

                for (auto & n : names)
                {
                    std::shared_ptr<const Reference> r;

                    TEST_CHECK_NO_THROW(r = references[n]);

                    TEST_CHECK(r.get() != nullptr);
                }
            }
        }
} references_test;
