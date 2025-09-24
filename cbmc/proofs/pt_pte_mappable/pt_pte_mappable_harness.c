// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file pt_pte_mappable_harness.c
 * @brief Implements the proof harness for pt_pte_mappable function.
 */

#include <assert.h>
#include <mem.h>
#include <as_helpers.h>
#include <addr_helpers.h>

bool pt_pte_mappable(struct addr_space* as, pte_t* pte, size_t lvl, size_t left,
                     vaddr_t vaddr, paddr_t paddr);

/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    struct addr_space *as;
    as = proof_as_allocate();
    proof_as_init(as);
    assert(proof_as_is_valid(as));

    pte_t pte;
    size_t lvl;
    __CPROVER_assume(lvl < 3);
    size_t left;
    __CPROVER_assume(left <= (PROOF_VADDR_SIZE / PAGE_SIZE));
    vaddr_t vaddr;
    __CPROVER_assume(proof_vaddr_is_valid(vaddr));
    paddr_t paddr;
    __CPROVER_assume(proof_paddr_is_valid(paddr));
    bool res;

    res = pt_pte_mappable(as, &pte, lvl, left, vaddr, paddr);
    /* PTE must be invalid... */
    assert(!res || !pte_valid(&pte));
    /* ...have enough space... */
    assert(!res || (pt_lvlsize(&as->pt, lvl) <= (left * PAGE_SIZE)));
    /* ...be correctly aligned... */
    assert(!res || ((vaddr % pt_lvlsize(&as->pt, lvl)) == 0));
    /* ...and paddr must be aligned */
    assert(!res || ((paddr % pt_lvlsize(&as->pt, lvl)) == 0));

    assert(proof_as_is_valid(as));
}
