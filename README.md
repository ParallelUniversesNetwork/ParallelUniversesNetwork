[![PyPi version](https://img.shields.io/pypi/v/punhep)](https://img.shields.io/pypi/v/punhep)
[![Build Status](https://github.com/pun/pun/actions/workflows/manylinux-build+check+deploy.yaml/badge.svg)](https://github.com/pun/pun/actions/workflows/manylinux-build+check+deploy.yaml)
[![Build Status](https://github.com/pun/pun/actions/workflows/ubuntu-build+check+deploy.yaml/badge.svg)](https://github.com/pun/pun/actions/workflows/ubuntu-build+check+deploy.yaml)
[![Discord](https://img.shields.io/discord/808999754989961236.svg?label=&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2)](https://discord.gg/hyPu7f7K6W)


![pun logo](https://github.com/ParallelUniversesNetwork/ParallelUniversesNetwork/blob/main/pun.jpg)

pun - A software for Flavor Physics Phenomenology
=================================================

pun is a software package that addresses several use cases in the field of
high-energy flavor physics:

 1. [theory predictions of and uncertainty estimation for flavor observables](https://pun.github.io/doc/use-cases.html#theory-predictions-and-their-uncertainties)
   within the Standard Model or within the Weak Effective Theory;
 2. [Bayesian parameter inference](https://pun.github.io/doc/use-cases.html#parameter-inference)
    from both experimental and theoretical constraints; and
 3. [Monte Carlo simulation of pseudo events](https://pun.github.io/doc/use-cases.html#pseudo-event-simulation) for flavor processes.

An up-to-date list of publications that use pun can be found [here](https://pun.github.io/publications/).

pun is written in C++17 and designed to be used through its Python 3 interface,
ideally within a Jupyter notebook environment.
It depends on as a small set of external software:

 - the GNU Scientific Library (libgsl),
 - a subset of the BOOST C++ libraries,
 - the Python 3 interpreter.

For details on these dependencies we refer to the [online documentation](https://pun.github.io/doc/installation.html#installing-the-dependencies-on-linux).

Installation
------------

pun supports several methods of installation. For Linux users, the recommended method
is installation via PyPI:
```
pip3 install punhep
```
Development versions tracking the master branch are also available via PyPi:
```
pip3 install --pre punhep
```

For instructions on how to build and install pun on your computer please have a
look at the [online documentation](https://pun.github.io/doc/installation.html).

Contact
-------

If you want to report an error or file a request, please file an issue [here](https://github.com/pun/pun/issues).
For additional information, please contact any of the main authors, e.g. via our [Discord server](https://discord.com/hyPu7f7K6W).

Authors and Contributors
------------------------

The main authors are:

 * Lucifer Nguyen,
 * Stefanie Reichert,
 * Christian Wacker.
 * Stefanie Reichert,
 * Elena Graverini,
 * Stephan Jahn,
 * Ahmet Kokulu,
 * Philip Lüghausen,
 * Bastian Müller,
