/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2011 Frederik Beaujean
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

#ifndef pun_GUARD_SRC_STATISTICS_PRIOR_HH
#define pun_GUARD_SRC_STATISTICS_PRIOR_HH 1

#include <pun/statistics/log-prior-fwd.hh>
#include <pun/utils/parameters.hh>
#include <pun/utils/wrapped_forward_iterator.hh>

#include <vector>
#include <memory>

#include  <gsl/gsl_rng.h>

namespace pun
{
    /*!
     * Base class for log(prior) distributions.
     *
     * Has a container of subclasses describing independent 1..k dimensional prior distributions.
     * Taken together, they specify the full N dimensional prior. Any actual calculation is done
     * by the subclasses.
     */
    class LogPrior
    {
        protected:
            /// Our associated Parameters object.
            Parameters _parameters;

            /// All parameters for which this prior provides information.
            std::vector<ParameterDescription> _parameter_descriptions;

        public:
            ///@name Basic Functions
            ///@{
            /*!
             * Constructor.
             *
             * @param parameters The Parameters objects from which we evaluate.
             */
            LogPrior(const Parameters & parameters);

            virtual ~LogPrior()
            {
            }

            virtual std::string as_string() const = 0;

            /*!
             * Create a clone (independent object) of this LogPrior object,
             *
             * @param parameters The Parameters object from which the clone shall evaluate.
             * @return The clone
             */
            virtual LogPriorPtr clone(const Parameters & parameters) const = 0;
            ///@}


            ///@name Iteration over descriptions
            ///@{
            struct IteratorTag;
            using Iterator = WrappedForwardIterator<IteratorTag, ParameterDescription>;

            Iterator begin();
            Iterator end();
            ///@}

            ///@name Accessors
            ///@{

            /*!
             * Evaluate the natural logarithm of the prior.
             */
            virtual double operator() () const = 0;

            /*!
             * Evaluate the inverse cumulative density function of the prior.
             *
             * @param p The cumulative probability for which we seek the parameter value.
             */
            virtual double inverse_cdf(const double & p) const = 0;

            /*!
             * Return the mean of the distribution.
             */
            virtual double mean() const = 0;

            /*!
             * Return the variance of this distribution.
             */
            virtual double variance() const = 0;

            /*!
             * Return whether or not this prior is informative.
             */
            virtual bool informative() const = 0;
            ///@}

            ///@name Named constructors for 1D prior distributions
            ///@{
            static LogPriorPtr Flat(const Parameters & parameters, const std::string & name, const ParameterRange & range);
            static LogPriorPtr Gauss(const Parameters & parameters, const std::string & name, const ParameterRange & range,
                    const double & lower, const double & central, const double & upper);
            static LogPriorPtr Scale(const Parameters & parameter, const std::string & name, const ParameterRange & range,
                    const double & mu_0, const double & lambda);

            /*!
             * Construct a prior from its string representation.
             *
             * @param parameters The object from which the value of the parameter is retrieved.
             * @param serialization The prior in string form.
             * @return Pointer to the ready made prior.
             */
            static LogPriorPtr Make(const Parameters & parameters, const std::string & serialization);
            ///@}
    };

    extern template class WrappedForwardIterator<LogPrior::IteratorTag, ParameterDescription>;
}

#endif
