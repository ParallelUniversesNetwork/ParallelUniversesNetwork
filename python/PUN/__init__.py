# Copyright (c) 2018 Frederik Beaujean
# Copyright (c) 2017, 2018, 2020 Danny van Dyk
# Copyright (c) 2021 Philip Lueghausen
#
# This file is part of the pun project. pun is free software;
# you can redistribute it and/or modify it under the terms of the GNU General
# Public License version 2, as published by the Free Software Foundation.
#
# pun is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc., 59 Temple
# Place, Suite 330, Boston, MA  02111-1307  USA

"""
pun is a software package that addresses several use cases in the field of
high-energy flavor physics (HEP).

Find documentation online at pun.github.io
Visit us at github.com/pun/pun

"""

from .config import *

# make sure that pun_HOME points to the location of the wheel supplied data
# if unset.
import os as _os
try:
    if is_wheel:
        if not 'pun_HOME' in _os.environ:
            _os.environ['pun_HOME'] = _os.path.normpath(_os.path.join(_os.path.dirname(__file__), '..', '_pun_data/'))
except NameError:
    pass

from _pun import *
from _pun import __version__
from .data import *
from .plot import *
from .analysis import Analysis, BestFitPoint
from .analysis_file import AnalysisFile
from .constraint import Constraints
from .observable import Observables
from .parameter import Parameters
from .reference import References
from .signal_pdf import SignalPDF, SignalPDFs
from .tasks import *

import logging
logger = logging.getLogger('pun')
logger.setLevel(logging.INFO)
from _pun import _register_log_callback, _set_native_log_level, _NativeLogLevel
_set_native_log_level(_NativeLogLevel.INFO) # default native log level

def debug(msg, *args, **kwargs):
    logger.debug(msg, *args, **kwargs)

def error(msg, *args, **kwargs):
    logger.error(msg, *args, **kwargs)

def info(msg, *args, **kwargs):
    logger.info(msg, *args, **kwargs)

def warn(msg, *args, **kwargs):
    logger.warning(msg, *args, **kwargs)

def _log_callback(id, level, msg):
    full_msg = '{id} {msg}'.format(id=id, msg=msg)

    if   level == _NativeLogLevel.INFO:
        logger.info(full_msg)
    elif level == _NativeLogLevel.DEBUG:
        logger.debug(full_msg)
    elif level == _NativeLogLevel.WARNING:
        logger.warning(full_msg)
    elif level == _NativeLogLevel.ERROR:
        logger.error(full_msg)
    elif level == _NativeLogLevel.SILENT:
        pass
    else:
        raise RuntimeError('Cannot handle log level: {ll}. Log message: {msg}'.format(ll=level, msg=full_msg))

_register_log_callback(_log_callback)

import time as _time
import os as _os
def installation_time():
    return _time.ctime(_os.path.getmtime(pun.__file__))

def installation_dir():
    return _os.path.dirname(pun.__file__)

__ipython__ = False
try:
    if __IPYTHON__:
        __ipython__ = True
        ip = get_ipython()
        html_formatter = ip.display_formatter.formatters['text/html']

        from .ipython import __format_Parameter, __format_KinematicVariable, __format_Kinematics, __format_Options
        from .ipython import __format_Observable, __format_ObservableEntry, __format_GoodnessOfFit, __format_Reference
        html_formatter.for_type(Parameter, __format_Parameter)
        html_formatter.for_type(KinematicVariable, __format_KinematicVariable)
        html_formatter.for_type(Kinematics, __format_Kinematics)
        html_formatter.for_type(Options, __format_Options)
        html_formatter.for_type(Observable, __format_Observable)
        html_formatter.for_type(ObservableEntry, __format_ObservableEntry)
        html_formatter.for_type(GoodnessOfFit, __format_GoodnessOfFit)
        html_formatter.for_type(Reference, __format_Reference)

        # print logger in notebook
        import logging
        logger = logging.getLogger('pun')
        logger.setLevel(logging.INFO)
        logging.basicConfig(stream=sys.stderr, level=logging.INFO)
except NameError as e:
    pass
