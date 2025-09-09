#include <as_helpers.h>
#include <pt_helpers.h>
#include <stdlib.h>

struct addr_space * proof_as_allocate(void)
{
    struct addr_space *as;
    
    /* Allocation of struct addr_space */
    as = malloc(sizeof(struct addr_space));
    __CPROVER_assume(as != NULL);
    return as;
}

void proof_as_init(struct addr_space *as)
{
    enum AS_TYPE type;
    __CPROVER_assume(type == AS_HYP || type == AS_HYP_CPY); // to add: AS_VM
    cpumap_t cpus;      // the cpus associated with this address space
    colormap_t colors;  // when using cache coloring, the colors that can be allocated for this address space
    asid_t id;          // global id
    spinlock_t lock;

    /* Initialization of struct addr_space */
    proof_pt_init(&(as->pt));
    as->type = type;
    as->cpus = cpus;
    as->colors = colors;
    as->id = id;
    as->lock = SPINLOCK_INITVAL;
}

bool proof_as_is_valid(struct addr_space *as)
{
    if (as == NULL) return false;
    if (!proof_pt_is_valid(&as->pt)) return false;
    return true;
}
