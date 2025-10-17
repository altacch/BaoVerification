// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file mem_alloc_pt_harness.c
 * @brief Implements the proof harness for mem_alloc_pt function.
 */

#include <assert.h>
#include <page_table.h>  // stubbed
#include <as_helpers.h>
#include <addr_helpers.h>

pte_t* mem_alloc_pt(struct addr_space* as, pte_t* parent, size_t lvl, vaddr_t addr);

/* Stubs */
void spin_lock(spinlock_t* lock) { }
void spin_unlock(spinlock_t* lock) { }
void fence_sync_write(void) { }

bool alloc_successful;

struct ppages mem_alloc_ppages(colormap_t colors, size_t num_pages, bool aligned)
{
    struct ppages pages = { .num_pages = 0 };

    if (alloc_successful) {
        pages.num_pages = num_pages;
    }
    return pages;
}

pte_t* pt_get_pte(struct page_table* pt, size_t lvl, vaddr_t va)
{
    size_t i;
    __CPROVER_assume(i < ROOT_SIZE);
    return pt->root[i];
}

pte_t* pt_get(struct page_table* pt, size_t lvl, vaddr_t va)
{
    return pt_get_pte(pt, lvl, va);
}


/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    struct addr_space *as;
    as = proof_as_allocate();
    proof_as_init(as);
    proof_pt_fill(&as->pt, 4);
    assert(proof_as_is_valid(as));

    /* This needs to be done here since cbmc does not handle well
       non-determinism for global variables */
    bool ok;
    alloc_successful = ok;

    size_t lvl;
    __CPROVER_assume(lvl < 2);
    vaddr_t addr;
    __CPROVER_assume(proof_vaddr_is_valid(addr));
    
    pte_t *pte = pt_get_pte(&as->pt, lvl, addr);
    pte_t *res = mem_alloc_pt(as, pte, lvl, addr);
    assert((!alloc_successful && res == NULL) ||
           (alloc_successful && res != NULL));
    assert(proof_as_is_valid(as));
}
