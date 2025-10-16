#include <pt_helpers.h>
#include <stdlib.h>
#include <assert.h>

/* Helpers for page table struct */

struct page_table * proof_pt_allocate(void)
{
    /* Allocation of struct page_table */
    struct page_table *pt;
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

    /* Initialization of root array */
    for (size_t i = 0; i < ROOT_SIZE; i++) {
        pte_set(&pt->root[i], 0, PTE_INVALID, PTE_RSW_EMPT);
    }
}

bool proof_pt_is_valid(struct page_table *pt)
{
    if (pt == NULL) return false;
    if (pt->root == NULL) return false;
    for (size_t i = 0; i < ROOT_SIZE; i++) {
        if (pte_valid(&pt->root[i]) && pte_addr(&pt->root[i]) == NULL) return false;
    }
    if (pt->dscr != hyp_pt_dscr) return false;
    return true;
}

/* Helpers for hierarchical page table */

void proof_pt_fill(struct page_table *pt, size_t m)
/* Fills an empty page table at every address that is a multiple of m */
{
    /* Requires at least one address in each leaf table */
    assert(m != 0 && m <= ROOT_SIZE);

    /* Build level 1 tables */
    for (size_t i = 0; i < ROOT_SIZE; i++) {
        pte_t *root_l1 = proof_pt_root_allocate();
        pte_set(&pt->root[i], root_l1, PTE_TABLE, PTE_HYP_FLAGS);

        /* Build level 2 tables */
        for (size_t j = 0; j < ROOT_SIZE; j++) {
            pte_t *root_l2 = proof_pt_root_allocate();
            pte_set(&root_l1[j], root_l2, PTE_TABLE, PTE_HYP_FLAGS);

            /* Fill level 3 tables */
            for (size_t k = 0; k < ROOT_SIZE; k++) {
                if (k % m == 0) {
                    uint8_t *page = malloc(PAGE_SIZE);
                    __CPROVER_assume(page != NULL);
                    pte_set(&root_l2[k], page, PTE_PAGE, PTE_HYP_FLAGS);
                } else {
                    pte_set(&root_l2[k], NULL, PTE_INVALID, 0);
                }
            }
        }
    }
}

// to be adjusted
bool proof_hier_pt_is_valid(struct page_table *pt)
{
    if (pt == NULL) return false;
    if (pt->root == NULL) return false;
    if (pt->dscr != hyp_pt_dscr) return false;
    for (size_t i = 0; i < ROOT_SIZE; i++) {
        pte_t *root_l1 = (pte_t *) pte_addr(&pt->root[i]);
        if (root_l1 == NULL) return false;
        for (size_t j = 0; j < ROOT_SIZE; j++) {
            pte_t *root_l2 = (pte_t *) pte_addr(&root_l1[j]);
            if (root_l2 == NULL) return false;
        }
    }
    return true;
}

