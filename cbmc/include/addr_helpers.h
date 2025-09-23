#include <types.h>

/* Virtual addesses are assumed to be less than this value */
#define PROOF_VADDR_SIZE 0x8000000000U  // 39-bits, adequate for RISC-V Sv39
/* Other possible values:
  0x1000U (12-bit, no address translation)
  0x200000U (21-bit, single level PT)
  0x40000000U (30-bit, 2-level PT) */

/* Physical addesses are assumed to be less than this value */
#define PROOF_PADDR_SIZE 0x8000000000U  // may be increased if necessary

/* Validity predicate for virtual and physical addresses */
static inline bool proof_vaddr_is_valid(vaddr_t vaddr)
{
    return (vaddr < PROOF_VADDR_SIZE);
}

static inline bool proof_paddr_is_valid(paddr_t paddr)
{
    return (paddr < PROOF_PADDR_SIZE);
}

