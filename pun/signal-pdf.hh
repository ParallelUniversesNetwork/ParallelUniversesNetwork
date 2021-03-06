/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2015, 2016 Danny van Dyk
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

#ifndef pun_GUARD_pun_UTILS_SIGNAL_PDF_HH
#define pun_GUARD_pun_UTILS_SIGNAL_PDF_HH 1

#include <pun/utils/density.hh>
#include <pun/utils/exception.hh>
#include <pun/utils/iterator-range.hh>
#include <pun/utils/kinematic.hh>
#include <pun/utils/options.hh>
#include <pun/utils/parameters.hh>
#include <pun/utils/qualified-name.hh>

#include <string>
#include <memory>
namespace pun
{
    class KinematicRange
    {
        public:
            const char * name;

            const double min, max;

            const std::string description;

            operator const char * () const
            {
                return name;
            }
    };

    class SignalPDF;

    using SignalPDFPtr = std::shared_ptr<SignalPDF>;

    class SignalPDF :
        public Density
    {
        public:
            virtual const QualifiedName & name() const = 0;

            virtual double evaluate() const = 0;

            virtual double normalization() const = 0;

            virtual Kinematics kinematics() = 0;

            virtual Parameters parameters() = 0;

            virtual Options options() = 0;

            virtual DensityPtr clone() const = 0;

            virtual DensityPtr clone(const Parameters & parameters) const = 0;

            static SignalPDFPtr make(const QualifiedName & name, const Parameters & parameters, const Kinematics & kinematics, const Options & options);
    };

    /*!
     * SignalPDFEntry is internally used to keep track of the SignalPDFDescription and the SignalPDFFactory
     * for any given SignalPDF. This includes handling its construction (via the make() method), and
     * describing it (via the ostream & insert() method).
     */
    class SignalPDFEntry
    {
        public:
            friend std::ostream & operator<< (std::ostream &, const SignalPDFEntry &);

            SignalPDFEntry();

            virtual ~SignalPDFEntry();

            virtual SignalPDFPtr make(const Parameters &, const Kinematics &, const Options &) const = 0;

            /// Return the SignalPDF name
            virtual const QualifiedName & name() const = 0;

            /// Return the SignalPDF description
            virtual const std::string & description() const = 0;

            ///@name Iteration over our kinematic ranges
            ///@{
            struct KinematicRangeIteratorTag;
            using KinematicRangeIterator = WrappedForwardIterator<KinematicRangeIteratorTag, const KinematicRange>;

            virtual KinematicRangeIterator begin_kinematic_ranges() const = 0;
            virtual KinematicRangeIterator end_kinematic_ranges() const = 0;

            inline IteratorRange<KinematicRangeIterator> kinematic_ranges() const
            {
                return IteratorRange<KinematicRangeIterator>(begin_kinematic_ranges(), end_kinematic_ranges());
            }
            ///@}

        protected:
            virtual std::ostream & insert(std::ostream & os) const = 0;
    };

    extern template class WrappedForwardIterator<SignalPDFEntry::KinematicRangeIteratorTag, const KinematicRange>;

    /*!
     * Output stream operator for SignalPDFEntry.
     */
    inline std::ostream & operator<< (std::ostream & os, const SignalPDFEntry & entry)
    {
        return entry.insert(os);
    }

    /*!
     * Container around the known and implemented signal PDFs
     */
    class SignalPDFs :
        public PrivateImplementationPattern<SignalPDFs>
    {
        public:
            /// Constructor.
            SignalPDFs();

            /// Destructor.
            ~SignalPDFs();

            ///@name Iteration over known constraints
            ///@{
            struct SignalPDFIteratorTag;
            using SignalPDFIterator = WrappedForwardIterator<SignalPDFIteratorTag, std::pair<const QualifiedName, std::shared_ptr<SignalPDFEntry>>>;

            SignalPDFIterator begin() const;
            SignalPDFIterator end() const;
            ///@}
    };

    /*!
     * SignalPDFNameError is thrown when SignalPDF::make encounters a malformed observable name.
     */
    struct SignalPDFNameError :
        public Exception
    {
        ///@name Basic Functions
        ///@{
        /*!
         * Constructor.
         *
         * @param name The offending malformed observable name.
         */
        SignalPDFNameError(const std::string & name);
        ///@}
    };
}

#endif
