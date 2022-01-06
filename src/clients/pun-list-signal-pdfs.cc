/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2016, 2017 Danny van Dyk
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

#include "cli_handler.hh"
#include "cli_error.hh"

#include <pun/signal-pdf.hh>
#include <pun/utils/destringify.hh>
#include <pun/utils/instantiation_policy-impl.hh>
#include <pun/utils/log.hh>
#include <pun/utils/parameters.hh>
#include <pun/utils/qualified-name.hh>
#include <pun/utils/stringify.hh>

#include <iostream>

using namespace pun;

using std::cerr;
using std::cout;
using std::endl;

struct CommandLine :
    cli::DefaultHandler
{
    virtual std::string app_name() const { return "pun-list-signal-pdfs"; }

    virtual std::string app_synopsis() const
    {
        return "A commandline client to list the available Signal PDFs implemented in pun.";
    }

    virtual std::string app_description() const { return ""; }

    // filter options
    cli::Group g_filter_options;
    cli::StringListArg a_filter_by_name;
    cli::StringListArg a_filter_by_prefix;

    CommandLine() :
        g_filter_options(main_options_section(), "Filter Options", "Options that filter out specific constraints"),
        a_filter_by_name(&g_filter_options,   "filter-by-name",   'n', "add a filter for the full constraint name"),
        a_filter_by_prefix(&g_filter_options, "filter-by-prefix", 'p', "add a filter for the constraint prefixes")
    {
    }
};

struct Filter
{
    std::set<qnp::Name> names;
    std::set<qnp::Prefix> prefixes;

    Filter(const CommandLine & cmd) :
        names(cmd.a_filter_by_name.begin_args(), cmd.a_filter_by_name.end_args()),
        prefixes(cmd.a_filter_by_prefix.begin_args(), cmd.a_filter_by_prefix.end_args())
    {
    }

    bool empty()
    {
        return names.empty() && prefixes.empty();
    }

    bool operator() (const std::pair<const QualifiedName, std::shared_ptr<SignalPDFEntry>> & arg)
    {
        if (prefixes.find(arg.first.prefix_part()) != prefixes.end())
            return true;

        if (names.find(arg.first.name_part()) != names.end())
            return true;

        return false;
    }
};

struct Printer
{
    void print(const std::shared_ptr<SignalPDFEntry> & rhs)
    {
        cout << rhs->name() << endl;

        cout << "    " << rhs->description() << endl;

        cout << endl;

        for (const auto & k : rhs->kinematic_ranges())
        {
            cout.fill(' ');

            cout.width(20);
            cout << std::right;
            cout << k.name;
            cout << std::left;

            cout.width(0);
            cout << " [ ";

            cout.width(10);
            cout << k.min;

            cout.width(0);
            cout << " , ";

            cout.width(10);
            cout << k.max;

            cout.width(0);
            cout << " ] : ";

            cout << k.description;

            cout << endl;
        }

        cout << endl;
    }
};

int main(int argc, char ** argv)
{
    try
    {
        CommandLine cmdline;
        cmdline.run(argc, argv, "pun-list-signal-pdfs");

        if (cmdline.a_help.specified())
        {
            if (cmdline.begin_usage_lines() != cmdline.end_usage_lines())
            {
                cout << "usage: ";
                for (cli::Handler::UsageLineConstIterator u_begin(cmdline.begin_usage_lines()), u(u_begin), u_end(cmdline.end_usage_lines()) ;
                        u != u_end ; ++u)
                {
                    if (u != u_begin)
                        cout << "       ";
                    cout << cmdline.app_name() << " " << *u << endl;
                }
            }
            cout << endl;
            cout << cmdline;
            return EXIT_SUCCESS;
        }
        else if (cmdline.a_version.specified())
        {
            cout << "0.0";
            cout << endl;
            return EXIT_SUCCESS;
        }

        SignalPDFs signal_pdfs;
        Filter filter(cmdline);
        Printer printer;

        if (filter.empty())
        {
            for (auto s : signal_pdfs)
                printer.print(s.second);

            return EXIT_SUCCESS;
        }

        for (auto s : signal_pdfs)
        {
            if (! filter(s))
                continue;

            printer.print(s.second);
        }
    }
    catch (const cli::DoHelp & h)
    {
        if (h.message.empty())
            cout << "Usage: " << argv[0] << " COMMAND [ARGS]" << endl;
        else
            cerr << "Usage error: " << h.message << endl;

        return EXIT_FAILURE;
    }
    catch (const Exception & e)
    {
        cerr << endl;
        cerr << "Error:" << endl;
        cerr << "  * " << e.what() << endl;
//        cerr << "  * " << e.backtrace("\n  * ") << e.message() << " (" << e.what() << ")" << endl;
        cerr << endl;
        return EXIT_FAILURE;
    }
}

#if 0

int
main(int argc, char * argv[])
{
    try
    {
        CommandLine::instance()->parse(argc, argv);

        SignalPDFs signal_pdfs;

        for (auto p = signal_pdfs.begin(), p_end = signal_pdfs.end() ; p != p_end ; ++p)
        {
            std::cout
                << p->first << ":\n"
                << *p->second << "\n"
                << std::endl;
        }
    }
    catch(DoUsage & e)
    {
        std::cout << e.what() << std::endl;
        std::cout << "Usage: pun-list-signal-pdfs" << std::endl;

        std::cout << "Print the database of implemented signal PDFs." << std::endl;
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
#endif
