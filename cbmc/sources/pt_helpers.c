#include <pt_helpers.h>
#include <stdlib.h>

/* Helpers for page table struct */

struct page_table * proof_pt_allocate(void)
{
    struct page_table *pt;

    /* Allocation of struct page_table */
    pt = malloc(sizeof(struct page_table));
    __CPROVER_assume(pt != NULL);
    return pt;
}

pte_t *proof_pt_root_allocate()
{
    /* Allocation of root array */
    pte_t *root = malloc(ROOT_SIZE * sizeof(pte_t));
    __CPROVER_assume(root != NULL);
    return root;
}
    
void proof_pt_init(struct page_table *pt)
{
    /* Initialization of struct page_table */
    pt->root = proof_pt_root_allocate();
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

/* Helpers for hierarchical page table */

struct page_table * proof_hier_pt_allocate(void)
{
    /* Build level 0 table */
    struct page_table *pt;
    pt = proof_pt_allocate();
    proof_pt_init(pt);
    proof_hier_pt_init(pt);
    return pt;
}

void proof_hier_pt_init(struct page_table *pt)
{
    /* Build level 1 tables */
    for (size_t i = 0; i < ROOT_SIZE; i++) {
        pte_t *root_l1 = proof_pt_root_allocate();
        pt->root[i] = root_l1;

        /* Build level 2 tables */
        for (size_t j = 0; j < ROOT_SIZE; j++) {
            pte_t *root_l2 = proof_pt_root_allocate();
            root_l1[j] = root_l2;
        }
    }
}

bool proof_hier_pt_is_valid(struct page_table *pt)
{
    if (pt == NULL) return false;
    if (pt->root == NULL) return false;
    if (pt->dscr != hyp_pt_dscr) return false;
    for (size_t i = 0; i < ROOT_SIZE; i++) {
        pte_t *root_l1 = pt->root[i];
        if (root_l1 == NULL) return false;        
        for (size_t j = 0; j < ROOT_SIZE; j++) {
            pte_t *root_l2 = root_l1[j];
            if (root_l2 == NULL) return false;
        }
    }
    return true;
}
