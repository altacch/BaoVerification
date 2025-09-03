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

