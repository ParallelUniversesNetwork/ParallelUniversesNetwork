# vim: set sw=4 sts=4 et tw=120 :

# Copyright (c) 2020-2021 Danny van Dyk
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
import logging
import numpy as _np
import os
import pypmc

def sample_mcmc(analysis_file, posterior, chain, base_directory='./', pre_N=150, preruns=3, N=1000, stride=5, cov_scale=0.1, start_point=None):
    """
    Samples from a named posterior PDF using Markov Chain Monte Carlo (MCMC) methods.

    The output file will be stored in pun_BASE_DIRECTORY/POSTERIOR/mcmc-CHAIN.

    :param analysis_file: The name of the analysis file that describes the named posterior, or an object of class `pun.AnalysisFile`.
    :type analysis_file: str or `pun.AnalysisFile`
    :param posterior: The name of the posterior PDF from which to draw the samples.
    :type posterior: str
    :param chain: The index assigned to the Markov chain. This value is used to seed the RNG for a reproducible analysis.
    :type chain: int >= 0
    :param base_directory: The base directory for the storage of data files. Can also be set via the pun_BASE_DIRECTORY environment variable.
    :type base_directory: str, optional
    :param pre_N: The number of samples to be used for an adaptation in each prerun steps. These samples will be discarded.
    :type pre_N: int, optional
    :param preruns: The number of prerun steps, which are used to adapt the MCMC proposal to the posterior.
    :type preruns: int, optional
    :param N: The number of samples to be stored in the output file. Defaults to 1000.
    :type N: int, optional
    :param stride: The ratio of samples drawn over samples stored. For every S samples, S - 1 will be discarded. Defaults to 5.
    :type stride: int, optional
    :param cov_scale: Scale factor for the initial guess of the covariance matrix.
    :type cov_scale: float, optional
    :param start_point: Optional starting point for the chain
    :type start_point: list-like, optional
    """

    output_path = os.path.join(base_directory, posterior, 'mcmc-{:04}'.format(int(chain)))
    _set_log_file(output_path, 'log')
    if type(analysis_file) is not pun.AnalysisFile:
        _analysis_file = pun.AnalysisFile(analysis_file)
    else:
        _analysis_file = analysis_file
    analysis = _analysis_file.analysis(posterior)
    rng = _np.random.mtrand.RandomState(int(chain) + 1701)
    try:
        samples, weights = analysis.sample(N=N, stride=stride, pre_N=pre_N, preruns=preruns, rng=rng, cov_scale=cov_scale, start_point=start_point)
        pun.data.MarkovChain.create(output_path, analysis.varied_parameters, samples, weights)
    except RuntimeError as e:
        pun.error('encountered run time error ({e}) in parameter point:'.format(e=e))
        for p in analysis.varied_parameters:
            pun.error(' - {n}: {v}'.format(n=p.name(), v=p.evaluate()))


def find_clusters(posterior, base_directory='./', threshold=2.0, K_g=1, analysis_file=None):
    """
    Finds clusters among posterior MCMC samples, grouped by Gelman-Rubin R value, and creates a Gaussian mixture density.

    Finding clusters and creating a Gaussian mixture density is a necessary intermediate step before using the sample-pmc subcommand.
    The input files are expected in pun_BASE_DIRECTORY/POSTERIOR/mcmc-*. All MCMC input files present will be used in the clustering.
    The output files will be stored in pun_BASE_DIRECTORY/POSTERIOR/clusters.

    :param posterior: The name of the posterior.
    :type posterior: str
    :param base_directory: The base directory for the storage of data files. Can also be set via the pun_BASE_DIRECTORY environment variable.
    :type base_directory: str, optional
    :param threshold: The R value threshold. If two sample subsets have an R value larger than this threshold, they will be treated as two distinct clusters. Defaults to 2.0.
    :type threshold: float > 1.0, optional
    :param K_g: The number of mixture components per cluster. Default to 1.
    :type K_g: int >= 1, optional
    """

    import pathlib
    output_path = os.path.join(base_directory, posterior, 'clusters')
    _set_log_file(output_path, 'log')
    input_paths = [str(p) for p in pathlib.Path(os.path.join(base_directory, posterior)).glob('mcmc-*')]
    chains    = [pun.data.MarkovChain(path).samples for path in input_paths]
    n = len(chains[0])
    for chain in chains:
        assert len(chain) == n, 'Every chains must contain the same number of samples'

    groups = pypmc.mix_adapt.r_value.r_group([_np.mean(chain.T, axis=1) for chain in chains],
                           [_np.var (chain.T, axis=1, ddof=1) for chain in chains],
                           n, threshold)
    pun.info('Found {} groups using an R value threshold of {}'.format(len(groups), threshold))
    density   = pypmc.mix_adapt.r_value.make_r_gaussmix(chains, K_g=K_g, critical_r=threshold)
    pun.info(f'Created mixture density with {len(density.components)} components')
    pun.data.MixtureDensity.create(output_path, density)


def mixture_product(posterior, posteriors, base_directory='./', analysis_file=None):
    """
    Compute the cartesian product of the densities listed in posteriors. Note that this product is not commutative.

    The input densities are read from pun_BASE_DIRECTORY/POSTERIOR_i/pmc, where POSTERIOR_i is listed in posteriors.
    The output density will be stored in pun_BASE_DIRECTORY/POSTERIOR/product.

    :param posterior: The name of the posterior.
    :type posterior: str
    :param posteriors: The list of names of the posteriors whose mixture densities will be concatenated.
    :type posteriors: iterable of str
    :param base_directory: The base directory for the storage of data files. Can also be set via the pun_BASE_DIRECTORY environment variable.
    :type base_directory: str, optional
    """

    densities = [pun.data.PMCSampler(os.path.join(base_directory, p, 'pmc')).density() for p in posteriors]
    output_path = os.path.join(base_directory, posterior, 'product')
    pun.data.MixtureDensity.create(output_path, pun.data.MixtureDensity.cartesian_product(densities))


# Sample PMC
def sample_pmc(analysis_file, posterior, base_directory='./', step_N=500, steps=10, final_N=5000,
               perplexity_threshold=1.0, weight_threshold=1e-10, sigma_test_stat=None, initial_proposal='clusters'):
    """
    Samples from a named posterior using the Population Monte Carlo (PMC) methods.

    The results of the find-cluster command are expected in pun_BASE_DIRECTORY/POSTERIOR/clusters.
    The output file will be stored in pun_BASE_DIRECTORY/POSTERIOR/pmc.

    :param analysis_file: The name of the analysis file that describes the named posterior, or an object of class `pun.AnalysisFile`.
    :type analysis_file: str or `pun.AnalysisFile`
    :param posterior: The name of the posterior.
    :type posterior: str
    :param base_directory: The base directory for the storage of data files. Can also be set via the pun_BASE_DIRECTORY environment variable.
    :type base_directory: str, optional
    :param step_N: The number of samples to be used in each adaptation step. These samples will be discarded. Defaults to 500.
    :type step_N: int > 0, optional
    :param steps: The number of adaptation steps, which are used to adapt the PMC proposal to the posterior. Defaults to 10.
    :type steps: int > 0, optional
    :param final_N: The number of samples to be stored in the output file. Defaults to 5000,
    :type final_N: int > 0, optional
    :param perplexity_threshold: The threshold for the perplexity in the last step after which further adaptation steps are to be skipped. Defaults to 1.0.
    :type perplexity_threshold: 0.0 < float <= 1.0, optional
    :param weight_threshold: Mixture components with a weight smaller than this threshold are pruned.
    :type weight_threshold: 0.0 < float <= 1.0, optional.
    :param sigma_test_stat: If provided, the inverse CDF of -2*log(PDF) will be evaluated, using the provided values as the respective significance.
    :type sigma_test_stat: list or iterable
    :param initial_proposal: Specify where the initial proposal should be taken from; 'clusters' (default): use the proposal obtained using `find-clusters`;
    'product': use the proposal obtained from `mixture_product`; 'pmc': continue sampling from the previous `sample-pmc` results.
    :type initial_proposal: str, optional
     """

    output_path = os.path.join(base_directory, posterior, 'pmc')
    _set_log_file(output_path, 'log', mode='a' if (initial_proposal == 'pmc') else 'w')
    if type(analysis_file) is not pun.AnalysisFile:
        _analysis_file = pun.AnalysisFile(analysis_file)
    else:
        _analysis_file = analysis_file
    analysis = _analysis_file.analysis(posterior)
    rng = _np.random.mtrand.RandomState(1701)
    if initial_proposal == 'clusters':
        initial_density = pun.data.MixtureDensity(os.path.join(base_directory, posterior, 'clusters')).density()
    elif initial_proposal == 'pmc':
        previous_sampler = pun.data.PMCSampler(os.path.join(base_directory, posterior, 'pmc'))
        initial_density = previous_sampler.density()
    elif initial_proposal == 'product':
        initial_density = pun.data.MixtureDensity(os.path.join(base_directory, posterior, 'product')).density()
    else:
        pun.error("Could not initialize proposal in sample_pmc: argument {} is not supported.".format(initial_proposal))

    samples, weights, proposal = analysis.sample_pmc(initial_density, step_N=step_N, steps=steps, final_N=final_N,
                                                     rng=rng, final_perplexity_threshold=perplexity_threshold, weight_threshold=weight_threshold)

    if initial_proposal == 'pmc':
        samples = _np.concatenate((previous_sampler.samples, samples), axis=0)
        weights = _np.concatenate((previous_sampler.weights, weights), axis=0)

    pun.data.PMCSampler.create(output_path, analysis.varied_parameters, samples, weights, proposal, sigma_test_stat=sigma_test_stat)


# Predict observables
def predict_observables(analysis_file, posterior, prediction, base_directory='./', begin=0, end=-1):
    '''
    Predicts a set of observables based on previously obtained PMC samples.

    The input files are expected in pun_BASE_DIRECTORY/POSTERIOR/pmc.
    The output files will be stored in pun_BASE_DIRECTORY/POSTERIOR/pred-PREDICTION.

    :param analysis_file: The name of the analysis file that describes the named posterior, or an object of class `pun.AnalysisFile`.
    :type analysis_file: str or `pun.AnalysisFile`
    :param posterior: The name of the posterior.
    :type posterior: str
    :param prediction: The name of the set of observables to predict.
    :type prediction: str
    :param base_directory: The base directory for the storage of data files. Can also be set via the pun_BASE_DIRECTORY environment variable.
    :type base_directory: str, optional
    :param begin: The index of the first sample to use for the predictions. Defaults to 0.
    :type begin: int
    :param end: The index beyond the last sample to use for the predictions. Defaults to -1.
    :type begin: int
    '''
    _parameters = pun.Parameters()
    if type(analysis_file) is not pun.AnalysisFile:
        _analysis_file = pun.AnalysisFile(analysis_file)
    else:
        _analysis_file = analysis_file
    observables = _analysis_file.observables(prediction, _parameters)

    data = pun.data.PMCSampler(os.path.join(base_directory, posterior, 'pmc'))

    try:
        from tqdm import tqdm
        progressbar = tqdm
    except ImportError:
        progressbar = lambda x: x

    parameters = [_parameters[p['name']] for p in data.varied_parameters]
    observable_samples = []
    for i, sample in enumerate(progressbar(data.samples[begin:end])):
        for p, v in zip(parameters, sample):
            p.set(v)
        try:
            observable_samples.append([o.evaluate() for o in observables])
        except RuntimeError as e:
            pun.error('skipping prediction for sample {i} due to runtime error ({e}): {s}'.format(i=i, e=e, s=sample))
            observable_samples.append([_np.nan for o in observables])
    observable_samples = _np.array(observable_samples)

    output_path = os.path.join(base_directory, posterior, 'pred-{}'.format(prediction))
    pun.data.Prediction.create(output_path, observables, observable_samples, data.weights[begin:end])


# Run analysis steps
def run_steps(analysis_file, base_directory='./'):
    """
    Runs a list of predefined steps recorded in the analysis file.

    Each step corresponds to a call to one of the following common tasks:
     - sample-mcmc
     - find-cluster
     - sample-pmc
     - predict-observables

    :param analysis_file: The name of the analysis file that describes the named posterior, or an object of class `pun.AnalysisFile`.
    :type analysis_file: str or `pun.AnalysisFile`
    """
    if type(analysis_file) is not pun.AnalysisFile:
        _analysis_file = pun.AnalysisFile(analysis_file)
    else:
        _analysis_file = analysis_file
    _analysis_file.run()


def _set_log_file(path, name='log', mode='w'):
    os.makedirs(path, exist_ok=True)
    formatter = logging.Formatter('%(asctime)-15s %(name)-5s %(levelname)-8s %(message)s')
    handler = logging.FileHandler(os.path.join(path, name), mode=mode)
    handler.setFormatter(formatter)
    pun.logger.addHandler(handler)
