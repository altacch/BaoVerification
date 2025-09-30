HARNESS_ENTRY = harness
HARNESS_FILE = mem_expand_pte_harness

# This should be a unique identifier for this proof, and will appear on the
# Litani dashboard. It can be human-readable and contain spaces if you wish.
PROOF_UID = mem_expand_pte

DEFINES += -DIRQC=PLIC -DROOT_SIZE=4 -DRV_XLEN=64
INCLUDES += -I$(PROOF_STUB)/core/inc
INCLUDES += -I$(SRCDIR)/bao-hypervisor/src/lib/inc/ -I$(SRCDIR)/bao-hypervisor/src/core/inc/ -I$(SRCDIR)/bao-hypervisor/src/core/mmu/inc/ -I$(SRCDIR)/bao-hypervisor/src/arch/riscv/inc/ -I$(SRCDIR)/bao-hypervisor/src/platform/drivers/sbi_uart/inc -I$(SRCDIR)/bao-hypervisor/src/platform/qemu-riscv64-virt/inc/ -I$(SRCDIR)/bao-hypervisor/src/arch/riscv/irqc/plic/inc/
INCLUDES += -I $(PROOF_INCLUDE)

REMOVE_FUNCTION_BODY += fence_sync_write tlb_inv_va mem_alloc_pt
UNWINDSET += proof_hier_pt_init.0:5 proof_hier_pt_init.1:5 proof_hier_pt_is_valid.0:5 proof_hier_pt_is_valid.1:5
UNWINDSET += pt_get_pte.0:5 mem_expand_pte.0:5

PROOF_SOURCES += $(PROOFDIR)/$(HARNESS_FILE).c $(PROOF_SOURCE)/pt_helpers.c $(PROOF_SOURCE)/as_helpers.c
PROJECT_SOURCES += $(SRCDIR)/bao-hypervisor/src/arch/riscv/page_table.c $(SRCDIR)/bao-hypervisor/src/core/mem.c $(PROOF_SOURCE)/core_mmu_mem.c

# If this proof is found to consume huge amounts of RAM, you can set the
# EXPENSIVE variable. With new enough versions of the proof tools, this will
# restrict the number of EXPENSIVE CBMC jobs running at once. See the
# documentation in Makefile.common under the "Job Pools" heading for details.
# EXPENSIVE = true

# If you require access to a file-local ("static") function or object to conduct
# your proof, set the following (and do not include the original source file
# ("bao-hypervisor/src/core/mmu/mem.c") in PROJECT_SOURCES).
# REWRITTEN_SOURCES = $(PROOFDIR)/mem.i
# include ../Makefile.common
# $(PROOFDIR)/mem.i_SOURCE = $(SRCDIR)/bao-hypervisor/src/core/mmu/mem.c
# $(PROOFDIR)/mem.i_FUNCTIONS = mem_alloc_pt
# $(PROOFDIR)/mem.i_OBJECTS = 
# Care is required with variables on the left-hand side: REWRITTEN_SOURCES must
# be set before including Makefile.common, but any use of variables on the
# left-hand side requires those variables to be defined. Hence, _SOURCE,
# _FUNCTIONS, _OBJECTS is set after including Makefile.common.

include ../Makefile.common
