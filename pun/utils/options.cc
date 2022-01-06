/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2010, 2011, 2015, 2016, 2018 Danny van Dyk
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

#include <eos/utils/join.hh>
#include <eos/utils/options.hh>
#include <eos/utils/private_implementation_pattern-impl.hh>
#include <eos/utils/wrapped_forward_iterator-impl.hh>

#include <map>

namespace eos
{
    template <>
    struct WrappedForwardIteratorTraits<Options::OptionIteratorTag>
    {
        using UnderlyingIterator = std::map<std::string, std::string>::const_iterator;
    };
    template class WrappedForwardIterator<Options::OptionIteratorTag, const std::pair<const std::string, std::string>>;

    template <>
    struct Implementation<Options>
    {
        std::map<std::string, std::string> options;

        Implementation()
        {
        }

        Implementation(const std::initializer_list<std::pair<std::string, std::string>> & _options)
        {
            for (const auto & _option : _options)
            {
                options.insert(_option);
            }
        }
    };

    Options::Options() :
        PrivateImplementationPattern<Options>(new Implementation<Options>)
    {
    }

    Options::Options(const std::initializer_list<std::pair<std::string, std::string>> & options) :
        PrivateImplementationPattern<Options>(new Implementation<Options>(options))
    {
    }

    Options::~Options()
    {
    }

    bool
    Options::operator== (const Options & rhs) const
    {
        if (_imp->options.size() != rhs._imp->options.size())
            return false;

        for (auto l = _imp->options.cbegin(), l_end = _imp->options.cend(), r = rhs._imp->options.cbegin() ; l != l_end ; ++l, ++r)
        {
            if (*l != *r)
                return false;
        }

        return true;
    }

    bool
    Options::operator!= (const Options & rhs) const
    {
        return ! (*this == rhs);
    }

    const std::string &
    Options::operator[] (const std::string & key) const
    {
        auto i(_imp->options.find(key));
        if (_imp->options.end() == i)
            throw UnknownOptionError(key);

        return i->second;
    }

    bool
    Options::has(const std::string & key) const
    {
        return _imp->options.end() != _imp->options.find(key);
    }

    void
    Options::declare(const std::string & key, const std::string & value)
    {
        auto i(_imp->options.find(key));
        if (_imp->options.end() != i)
        {
            i->second = value;
        }
        else
        {
            _imp->options[key] = value;
        }
    }

    std::string
    Options::get(const std::string & key, const std::string & default_value) const
    {
        auto i(_imp->options.find(key));

        if (_imp->options.end() == i)
            return default_value;

        return i->second;
    }

    std::string
    Options::as_string() const
    {
        std::string result;

        auto i(_imp->options.cbegin()), i_end(_imp->options.cend());

        if (i != i_end)
        {
            result += i->first + '=' + i->second;
            ++i;
        }

        for ( ; i != i_end ; ++i)
        {
            result += ',' + i->first + '=' + i->second;
        }

        return result;
    }

    Options::OptionIterator
    Options::begin() const
    {
        return _imp->options.cbegin();
    }

    Options::OptionIterator
    Options::end() const
    {
        return _imp->options.cend();
    }

    bool
    Options::empty() const
    {
        return _imp->options.empty();
    }

    UnknownOptionError::UnknownOptionError(const std::string & key) throw () :
        Exception("Unknown option: '" + key + "'")
    {
    }

    InvalidOptionValueError::InvalidOptionValueError(const std::string & key, const std::string & value, const std::string & allowed) throw () :
        Exception("Invalid value '" + value + "' for option: '" + key + "'" + (allowed.empty() ? "" : ". Allowed values: '" + allowed + "'"))
    {
    }

    UnspecifiedOptionError::UnspecifiedOptionError(const std::string & key, const std::string & allowed) throw () :
        Exception("Mandatory option '" + key + "' not specified'" + (allowed.empty() ? "" : ". Allowed values: '" + allowed + "'"))
    {
    }

    Options
    operator+ (const Options & lhs, const Options & rhs)
    {
        Options result;

        result._imp->options.insert(lhs._imp->options.cbegin(), lhs._imp->options.cend());

        /*
         * merge all options from rhs into result. Make sure to overwrite
         * existing lhs options with the same key.
         */
        for (auto o : rhs._imp->options)
        {
            auto retval = result._imp->options.insert(o);

            if (! retval.second)
            {
                retval.first->second = o.second;
            }
        }

        return result;
    }

    SpecifiedOption::SpecifiedOption(const Options & options, const std::vector<OptionSpecification> & specifications, const std::string & key)
    {
        const auto s = std::find_if(specifications.cbegin(), specifications.cend(), [&] (const auto & e) -> bool {
            return e.key == key;
        });

        if (specifications.cend() == s)
            throw InternalError("Options key '" + key + "' is not specified in the options specifications");

        if (! options.has(key))
        {
            if ("" == s->default_value)
                throw UnspecifiedOptionError(key, join(s->allowed_values.cbegin(), s->allowed_values.cend()));

            _value = s->default_value;
        }
        else
        {
            _value = options[key];

            if (std::find(s->allowed_values.cbegin(), s->allowed_values.cend(), _value) == s->allowed_values.cend())
            {
                throw InvalidOptionValueError(key, _value, join(s->allowed_values.cbegin(), s->allowed_values.cend()));
            }
        }
    }

    SpecifiedOption::~SpecifiedOption() = default;

    const std::string &
    SpecifiedOption::value() const
    {
        return _value;
    }

    LeptonFlavorOption::LeptonFlavorOption(const Options & options, const std::vector<OptionSpecification> & specifications, const std::string & key) :
        SpecifiedOption(options, specifications, key)
    {
    }

    LeptonFlavorOption::~LeptonFlavorOption() = default;

    LeptonFlavor
    LeptonFlavorOption::value() const
    {
        static const std::map<std::string, LeptonFlavor> map
        {
            { "e",   LeptonFlavor::electron },
            { "mu",  LeptonFlavor::muon     },
            { "tau", LeptonFlavor::tauon    }
        };

        const auto i = map.find(_value);
        if (map.cend() == i)
            throw InternalError("Invalid lepton flavor '" + _value + "' encountered in LeptonFlavorOption::value()");

        return i->second;
    }

    const std::string &
    LeptonFlavorOption::str() const
    {
        return _value;
    }

    QuarkFlavorOption::QuarkFlavorOption(const Options & options, const std::vector<OptionSpecification> & specifications, const std::string & key) :
        SpecifiedOption(options, specifications, key)
    {
    }

    QuarkFlavorOption::~QuarkFlavorOption() = default;

    QuarkFlavor
    QuarkFlavorOption::value() const
    {
        static const std::map<std::string, QuarkFlavor> map
        {
            { "u", QuarkFlavor::up      },
            { "d", QuarkFlavor::down    },
            { "s", QuarkFlavor::strange },
            { "c", QuarkFlavor::charm   },
            { "b", QuarkFlavor::bottom  },
            { "t", QuarkFlavor::top     }
        };

        const auto i = map.find(_value);
        if (map.cend() == i)
            throw InternalError("Invalid quark flavor '" + _value + "' encountered in QuarkFlavorOption::value()");

        return i->second;
    }

    const std::string &
    QuarkFlavorOption::str() const
    {
        return _value;
    }
}
