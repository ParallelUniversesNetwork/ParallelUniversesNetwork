#!/usr/bin/python
# vim: set sw=4 sts=4 et tw=120 :

# Copyright (c) 2020 Danny van Dyk
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

import pun
import os
import yaml

class AnalysisFile:
    """Represents a collection of statistical analyses and their building blocks.

    :param analysis_file: The path to the file to be parsed.
    :type analysis_file: str
    """

    def __init__(self, analysis_file):
        """Constructor."""

        self.analysis_file = analysis_file

        if not os.path.exists(analysis_file):
            raise RuntimeError('Cannot load analysis file: \'{}\' does not exist'.format(analysis_file))

        if not os.path.isfile(analysis_file):
            raise RuntimeError('Cannot load analysis file: \'{}\' is not a file'.format(analysis_file))

        instructions = None
        with open(analysis_file) as input_file:
            input_data = yaml.load(input_file, Loader=yaml.SafeLoader)

        if 'priors' not in input_data:
            raise RuntimeError('Cannot load analysis file: need at least one prior')

        self._priors = { prior['name'] : dict(prior) for prior in input_data['priors'] }

        if 'likelihoods' not in input_data:
            self._likelihoods = []
        else:
            self._likelihoods = { lh['name'] : dict(lh) for lh in input_data['likelihoods'] }

        if 'posteriors' not in input_data:
            raise RuntimeError('Cannot load analysis file: need at least one posterior')

        self._posteriors = { posterior['name'] : dict(posterior) for posterior in input_data['posteriors'] }

        if 'predictions' not in input_data:
            self._predictions = []
        else:
            self._predictions = { pred['name'] : dict(pred) for pred in input_data['predictions'] }

        if 'steps' not in input_data:
            self._steps = []
        else:
            self._steps = input_data['steps']


    def analysis(self, _posterior):
        """Create an pun.Analysis object for the named posterior."""
        if _posterior not in self._posteriors:
            raise RuntimeError('Cannot create analysis for unknown posterior: \'{}\''.format(_posterior))

        posterior = self._posteriors[_posterior]

        prior = []
        for p in posterior['prior']:
            prior.extend(self._priors[p]['parameters'])

        likelihood = []
        manual_constraints = {}
        for lh in posterior['likelihood']:
            LH_ALLOWED_KEYS = { 'name', 'constraints', 'manual_constraints' }
            for key in self._likelihoods[lh]:
                if key not in LH_ALLOWED_KEYS:
                    raise KeyError(f"Unsupported key in 'likelihoods['{lh}']': {key}")

            if 'constraints' not in self._likelihoods[lh] and 'manual_constraints' not in self._likelihoods[lh]:
                raise KeyError(f'Missing entry in \'likelihoods[\'{lh}\']\': neither \'constraints\' nor \'manual_constraints\' is provided')

            likelihood.extend(self._likelihoods[lh]['constraints'] if 'constraints' in self._likelihoods[lh] else [])
            manual_constraints.update(self._likelihoods[lh]['manual_constraints'] if 'manual_constraints' in self._likelihoods[lh] else {})

        global_options = posterior['global_options'] if 'global_options' in posterior else {}
        fixed_parameters = posterior['fixed_parameters'] if 'fixed_parameters' in posterior else {}

        return pun.Analysis(prior, likelihood, global_options,
                            manual_constraints=manual_constraints,
                            fixed_parameters=fixed_parameters)


    def observables(self, _prediction, parameters):
        """Creates a list of pun.Observable objects for the named set of predictions."""
        if _prediction not in self.predictions:
            raise RuntimeError('Cannot create observables for unknown set of predictions: \'{}\''.format(_prediction))

        prediction = self.predictions[_prediction]
        options = pun.Options(**prediction['global_options'])
        observables = [pun.Observable.make(
            o['name'],
            parameters,
            pun.Kinematics(**(o['kinematics'] if 'kinematics' in o else {})),
            options
        ) for o in prediction['observables']]

        if None in observables:
            unknown_observables = set()
            for p, o in zip(prediction['observables'], observables):
                if o is None:
                    unknown_observables.add(p['name'])
            raise RuntimeError('Prediction \'{}\' contains unknown observable names: {}'.format(_prediction, unknown_observables))

        return observables


    @staticmethod
    def _sanitize_params(command, params):
        """Helper functions to sanitize parameters for individual steps loaded from a raw YAML file."""
        general_params_maps = {
            'b': 'base_directory'
        }
        specific_params_map = {
            # find-clusters
            ('find-clusters', 't'): 'threshold',
            ('find-clusters', 'c'): 'K_g', ('find-clusters', 'clusters-per-group'): 'K_g',
            # predict-observables
            ('predict-observables', 'B'): 'begin',
            ('predict-observables', 'E'): 'end',
            # sample-mcmc
            ('sample-mcmc', 'n'): 'pre_N', ('sample-mcmc', 'prerun-samples'): 'pre_N',
            ('sample-mcmc', 'p'): 'preruns',
            ('sample-mcmc', 'S'): 'stride',
            # sample-pmc
            ('sample-pmc', 'n'): 'step_N', ('sample-pmc', 'step-samples'): 'step_N',
            ('sample-pmc', 's'): 'steps',
            ('sample-pmc', 'N'): 'final_N', ('sample-pmc', 'final-samples'): 'final_N'

        }
        return {
            specific_params_map[(command, k)] if (command, k) in specific_params_map
            else general_params_map[k] if k in general_params_map
            else k
            for k, v in params.items()
        }

    def run(self):
        """Runs predefined analysis steps recorded in the analysis file."""
        import inspect
        command_map = {
            'find-clusters':       pun.find_clusters,
            'predict-observables': pun.predict_observables,
            'sample-mcmc':         pun.sample_mcmc,
            'sample-pmc':          pun.sample_pmc,
        }

        for idx, step in enumerate(self._steps):
            if type(step) is not dict:
                raise ValueError("Step #{} is not a key/value map.")

            if 'command' not in step:
                raise ValueError("Step #{} contains no command.")

            command  = step['command']
            func     = command_map[command]
            params   = step['parameters'] if 'parameters' in step else {}
            params   = { params_map[(command, k)]: v for k, v in params.items() }
            paramstr = ','.join(['{k}={v}'.format(k=k,v=v) for k, v in params])

            func_sig = inspect.signature(func)
            func_required_args = {}
            for n, p in func_sig.parameters.items():
                if p.default() != p.empty():
                    continue
                func_required_args += { n }
            for n in func_required_args:
                if n in params.keys():
                    continue
                pun.error('Mandatory argument \'{}\' not provided'.format(n))
                return

            pun.info('Beginning step #{i}: {cmd}({params})'.format(i=i,cmd=cmd, params=paramstr))
            func(**params)
            pun.info('Step #{i} complete'.format(i=i))


    @property
    def priors(self):
        """Returns a list of all priors recorded in the analysis file."""

        return self._priors


    @property
    def likelihoods(self):
        """Returns a list of all likelihoods recorded in the analysis file."""

        return self._likelihoods


    @property
    def posteriors(self):
        """Returns a list of all posteriors recorded in the analysis file."""

        return self._posteriors

    @property
    def predictions(self):
        """Returns a list of all predictions recorded in the analysis file."""

        return self._predictions


    def _repr_html_(self):
        result = r'''
        <table>
            <colgroup>
                <col width="100%" id="posterior"    style="min-width: 200px">
            </colgroup>
            <thead>
                <tr>
                    <th>posteriors</th>
                </tr>
            </thead>
            <tbody>
        '''
        for p in self._posteriors:
            result += fr'''
                <tr>
                    <td>{p}</td>
                </tr>
            '''

        result += r'''
            </tbody>
        </table>
        '''

        return result
