#include <pt_helpers.h>
#include <stdlib.h>

struct page_table * proof_pt_allocate(void)
{
    struct page_table *pt;

    /* Allocation of struct page_table */
    pt = malloc(sizeof(struct page_table));
    __CPROVER_assume(pt != NULL);
    return pt;
}

void proof_pt_init(struct page_table *pt)
{
    pte_t *root;
    
    /* Allocation of root array */
    root = malloc(ROOT_SIZE * sizeof(pte_t));
    __CPROVER_assume(root != NULL);
    
    /* Initialization of struct page_table */
    pt->root = root;
    pt->dscr = hyp_pt_dscr;   // to add: vm_pt_dscr
    /* pt.arch unconstrained */
}

bool proof_pt_is_valid(struct page_table *pt)
{
    if (pt == NULL) return false;
    if (pt->root == NULL) return false;
    if (pt->dscr != hyp_pt_dscr) return false;
    return true;
}

