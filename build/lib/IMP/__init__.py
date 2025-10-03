import os
from pkgutil import extend_path

# extend_path ensures that 'import IMP.foo' will search for the module 'foo'
# both in our build directory and in the regular IMP path
__oldpathlen = len(__path__)
__path__ = extend_path(__path__, __name__)

# If 'import IMP' pulls in *this* __init__.py, make sure we also do everything
# in the main IMP/__init__.py (should be the next element in the path) so that
# top-level stuff like IMP.deprecated_function is available.
with open(os.path.join(__path__[__oldpathlen], '__init__.py')) as fh:
    exec(fh.read())
del __oldpathlen, extend_path
