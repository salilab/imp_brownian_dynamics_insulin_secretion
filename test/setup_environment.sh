#!/usr/bin/env sh


DYLD_LIBRARY_PATH="/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/lib:/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/lib:/usr/local/lib:$DYLD_LIBRARY_PATH"
export DYLD_LIBRARY_PATH

PYTHONPATH="/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/lib:/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/lib:/usr/local/lib/python3.11/site-packages:$PYTHONPATH"
export PYTHONPATH

# Where to find data for the various modules
IMP_DATA="/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/data:/usr/local/share/IMP"
export IMP_DATA

# Extra places to look for imp modules
IMP_EXAMPLE_DATA="/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/doc/examples"
export IMP_EXAMPLE_DATA

# Location of binaries (for wine builds, which don't get PATH)
IMP_BIN_DIR="/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/bin"
export IMP_BIN_DIR

PATH="/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/bin:/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/module_bin/insulinsecretion:/usr/local/bin:$PATH"
export PATH


IMP_TMP_DIR="/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/tmp"
export IMP_TMP_DIR


mkdir -p "${IMP_TMP_DIR}"

exec ${precommand} "$@"