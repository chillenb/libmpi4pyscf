from __future__ import annotations

import importlib.metadata

import libmpi4pyscf as m


def test_version():
    assert importlib.metadata.version("libmpi4pyscf") == m.__version__
