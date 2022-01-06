/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2017 Danny van Dyk
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

#include <pun/observable.hh>
#include <pun/utils/destringify.hh>
#include <pun/utils/instantiation_policy-impl.hh>
#include <pun/utils/log.hh>
#include <pun/utils/parameters.hh>
#include <pun/utils/stringify.hh>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace pun;

class DoUsage
{
    private:
        std::string _what;

    public:
        DoUsage(const std::string & what) :
            _what(what)
        {
        }

        const std::string & what() const
        {
            return _what;
        }
};

class CommandLine :
    public InstantiationPolicy<CommandLine, Singleton>
{
    public:
        CommandLine()
        {
        }

        void parse(int argc, char ** argv)
        {
            Log::instance()->set_program_name("pun-list-observables");

            std::shared_ptr<Kinematics> kinematics(new Kinematics);

            for (char ** a(argv + 1), ** a_end(argv + argc) ; a != a_end ; ++a)
            {
                std::string argument(*a);

                throw DoUsage("Unknown command line argument: " + argument);
            }
        }
};

int
main(int argc, char * argv[])
{
    try
    {
        CommandLine::instance()->parse(argc, argv);

        Observables observables;

        for (auto o : observables)
        {
            std::cout
                << o.first << ":\n"
                << *o.second << "\n"
                << std::endl;
        }
    }
    catch(DoUsage & e)
    {
        std::cout << e.what() << std::endl;
        std::cout << "Usage: pun-list-observables" << std::endl;

        std::cout << "Print the database of implemented observables." << std::endl;
    }
    catch(Exception & e)
    {
        std::cerr << "Caught exception: '" << e.what() << "'" << std::endl;
        return EXIT_FAILURE;
    }
    catch(...)
    {
        std::cerr << "Aborting after unknown exception" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
