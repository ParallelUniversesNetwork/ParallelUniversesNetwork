/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2010, 2011, 2016 Danny van Dyk
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
#include <pun/utils/one-of.hh>
#include <pun/utils/stringify.hh>
#include <pun/utils/wilson-polynomial.hh>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>

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

struct ObservableInput
{
    ObservablePtr observable;
};

class CommandLine :
    public InstantiationPolicy<CommandLine, Singleton>
{
    public:
        Parameters parameters;

        std::list<std::string> coefficients;

        std::list<ObservableInput> inputs;

        CommandLine() :
            parameters(Parameters::Defaults())
        {
        }

        void parse(int argc, char ** argv)
        {
            Log::instance()->set_program_name("pun-print-polynomial");

            std::shared_ptr<Kinematics> kinematics(new Kinematics);

            for (char ** a(argv + 1), ** a_end(argv + argc) ; a != a_end ; ++a)
            {
                std::string argument(*a);
                if ("--coefficient" == argument)
                {
                    std::string coefficient = std::string(*(++a));
                    if (coefficients.cend() == std::find(coefficients.cbegin(), coefficients.cend(), coefficient))
                        coefficients.push_back(coefficient);

                    continue;
                }

                if ("--kinematics" == argument)
                {
                    std::string name = std::string(*(++a));
                    double value = destringify<double>(*(++a));
                    kinematics->declare(name);
                    kinematics->set(name, value);

                    continue;
                }

                if ("--observable" == argument)
                {
                    std::string name(*(++a));

                    ObservableInput input;
                    input.observable = Observable::make(name, parameters, *kinematics, Options());
                    if (! input.observable)
                        throw DoUsage("Unknown observable '" + name + "'");

                    inputs.push_back(input);
                    kinematics.reset(new Kinematics);

                    continue;
                }

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

        if (CommandLine::instance()->inputs.empty())
            throw DoUsage("No input specified");

        WilsonPolynomialEvaluator evaluator;
        WilsonPolynomialPrinter printer;
        for (auto i = CommandLine::instance()->inputs.cbegin(), i_end = CommandLine::instance()->inputs.cend() ; i != i_end ; ++i)
        {
            WilsonPolynomial polynomial = make_polynomial(i->observable, CommandLine::instance()->coefficients);

            std::cout << i->observable->name() << "[";

            auto c = CommandLine::instance()->coefficients.cbegin(), c_end = CommandLine::instance()->coefficients.cend();
            if (c != c_end)
            {
                std::cout << *c;
                ++c;
            }

            for ( ; c != c_end ; ++c)
            {
                std::cout << ", " << *c;
            }
            std::cout << "] = " << polynomial.accept_returning<std::string>(printer) << std::endl;
            std::cout << "polynomial = " << polynomial.accept_returning<double>(evaluator) << std::endl;
            std::cout << "direct     = " << i->observable->evaluate() << std::endl;
        }
    }
    catch(DoUsage & e)
    {
        std::cout << e.what() << std::endl;
        std::cout << "Usage: pun-print-polynomial" << std::endl;
        std::cout << "  [--coefficient WILSONCOEFFICIENT]*" << std::endl;
        std::cout << "  [[--kinematics NAME VALUE]* --observable NAME]+" << std::endl;
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
