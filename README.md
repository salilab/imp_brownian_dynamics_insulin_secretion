\brief Brownian dynamics simulations of insulin vesicle dynamics

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.23703930.svg)](https://doi.org/10.5281/zenodo.23703930)
[![Build Status](https://github.com/salilab/imp_brownian_dynamics_insulin_secretion/actions/workflows/build.yml/badge.svg?branch=main)](https://github.com/salilab/imp_brownian_dynamics_insulin_secretion/actions/workflows/build.yml)
[![codecov](https://codecov.io/gh/salilab/imp_brownian_dynamics_insulin_secretion/branch/main/graph/badge.svg)](https://codecov.io/gh/salilab/imp_brownian_dynamics_insulin_secretion)

The insulinsecretion module is a module for constructing data-driven
Brownian dynamics simulations of insulin vesicle dynamics in pancreatic β-cells.

# Info

_Author(s)_: Liping Sun

_Maintainer_: `L1P1NG`

_License_: [LGPL](http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html)
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

_Publications_:
- None

# Building from source in a nutshell:
- See https://integrativemodeling.org/latest/doc/manual/installation.html for general IMP installation instruction
- Make sure IMP prerequisites are installed
- Download IMP source code as explained in the installation manual
- Build IMP according to online instructions

# Installation:
- `$ cmake -DCMAKE_CXX_FLAGS="-std=c++17" .. -DCMAKE_BUILD_TYPE=Release`
- `$ make`
