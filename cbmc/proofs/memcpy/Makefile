HARNESS_ENTRY = harness
HARNESS_FILE = memcpy_harness

# This should be a unique identifier for this proof, and will appear on the
# Litani dashboard. It can be human-readable and contain spaces if you wish.
PROOF_UID = memcpy

DEFINES += -DARRAY_SIZE=40
INCLUDES += -nostdlib -I $(SRCDIR)/bao-hypervisor/src/lib/inc/ -I $(SRCDIR)/bao-hypervisor/src/core/inc/ -I $(SRCDIR)/bao-hypervisor/src/arch/riscv/inc/

REMOVE_FUNCTION_BODY +=
UNWINDSET += memcpy.0:41 memcpy.1:9
UNWINDSET += harness.0:41

PROOF_SOURCES += $(PROOFDIR)/$(HARNESS_FILE).c
PROJECT_SOURCES += $(SRCDIR)/bao-hypervisor/src/lib/string.c

include ../Makefile.common
