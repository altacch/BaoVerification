# BaoVerification

Prerequisites for running the proof checking scripts:

* check that the `bao-hypervisor` submodule has been fetched
* make sure that the following tools are available:
    * [cmbc](https://github.com/diffblue/cbmc), tested with version 6.3.1
    * [litani](https://github.com/awslabs/aws-build-accumulator), tested with version 1.29
    * (only if you want to add new proofs) [cbmc-starter-kit](https://github.com/model-checking/cbmc-starter-kit), tested with version 2.10 

After performing the steps above you should be able to run the script
`cbmc/proofs/run-cbmc-proofs.py` and get a nicely-formatted HTML report at the
path `cmbc/proofs/output/latest/html/index.html`.

## Reproducibility instructions

Please note that the results reported in the paper "Towards a formal
verification of the Bao Hypervisor" have been obtained running the proof
scripts on commit bfaff965ff333b8747b0eb4405bfe835b6ae046e (2025/09/02) of the
`bao-hypervisor` submodule.

## static qualifier removal

Unfortunately, the mechanism used in cbmc-starter-kit for removing `static`
qualifiers from source files does not seem to work on the Bao source tree.
To remedy this, before running the proofs related to static functions in
`core/mmu/mem.h` you must produce a modified version of that file with the
following command, launched from the root of the repository:

```bash
sed 's/^static //g' bao-hypervisor/src/core/mmu/mem.c > cbmc/sources/core_mmu_mem.c
```

This should be repeated each time you update the `bao-hypervisor` submodule.
