[//]: # (SPDX-License-Identifier: CC-BY-4.0)

# Building mlkem-native

### Prerequisites

To build **mlkem-native**, you need `make` and a C90 compiler. To use the test scripts, you need Python3 (>= 3.7).

### Using `make`

You can build and test **mlkem-native** as follows:

```bash
make quickcheck       # With native code backend (if available)
make OPT=0 quickcheck # With C backend
```

To merely build test and benchmarking components, use the following `make` targets:

```bash
make mlkem
make bench
make bench_components
make nistkat
make kat
```

The resulting binaries can then be found in `test/build`.

### Using `tests` script

We recommend compiling and running tests and benchmarks using the [`./scripts/tests`](scripts/tests) script. For
example,

```bash
./scripts/tests func
```

will compile and run functionality tests. For detailed information on how to use the script, please refer to the
`--help` option.

### Windows

You can also build **mlkem-native** on Windows using `nmake` and an MSVC compiler.

To build and run the tests (only support functional testing for non-opt implementation for now), use the following `nmake` targets:
```powershell
nmke /f .\Makefile.Microsoft_nmake quickcheck
```

# Developing mlkem-native

There are further scripts used for development of mlkem-native, such as `format`, `lint` and `autogenerate_files.py`, which have additional dependencies. You will also need CBMC if you make changes to the C code.

### nix setup

We specify the development environment for mlkem-native using nix. If you want to help develop mlkem-native, please setup nix using the [nix installer script](https://nixos.org/download/), not your package manager. 

All the development and build dependencies are specified in [flake.nix](flake.nix). To execute a bash shell, run
```bash
nix develop --experimental-features 'nix-command flakes'
```

To confirm that everything worked, try `lint` or `tests cbmc`.
