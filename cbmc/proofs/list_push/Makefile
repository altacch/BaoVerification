HARNESS_ENTRY = harness
HARNESS_FILE = list_push_harness

# This should be a unique identifier for this proof, and will appear on the
# Litani dashboard. It can be human-readable and contain spaces if you wish.
PROOF_UID = list_push

DEFINES +=
INCLUDES += -I $(SRCDIR)/bao-hypervisor/src/lib/inc -I $(SRCDIR)/bao-hypervisor/src/core/inc/ -I $(SRCDIR)/bao-hypervisor/src/arch/riscv/inc/

REMOVE_FUNCTION_BODY +=
UNWINDSET +=

PROOF_SOURCES += $(PROOFDIR)/$(HARNESS_FILE).c
PROJECT_SOURCES += $(PROOFDIR)/$(HARNESS_FILE).c

include ../Makefile.common
