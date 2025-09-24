// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file pte_allocable_harness.c
 * @brief Implements the proof harness for pte_allocable function.
 */

#include <assert.h>
#include <as_helpers.h>
#include <addr_helpers.h>
#include <page_table.h>
#include <mem.h>

bool pte_allocable(struct addr_space* as, pte_t* pte, size_t lvl, size_t left,
                   vaddr_t addr);

/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    struct addr_space* as;
    as = proof_as_allocate();
    proof_as_init(as);
    assert(proof_as_is_valid(as));

    size_t i;
    __CPROVER_assume(i < ROOT_SIZE);
    pte_t pte = as->pt.root[i];
    size_t lvl;
    __CPROVER_assume(lvl < 3);
    size_t left;
    __CPROVER_assume(left <= (PROOF_VADDR_SIZE / PAGE_SIZE));
    vaddr_t vaddr;
    __CPROVER_assume(proof_vaddr_is_valid(vaddr));
    bool res;

    res = pte_allocable(as, &pte, lvl, left, vaddr);
    /* A PTE at last level is always allocable */
    assert((lvl != 2) || res);
    /* A PTE not at last level must be terminal... */
    assert(!(res && (lvl < 2)) || pt_lvl_terminal(&as->pt, lvl));
    /* ...invalid... */
    assert(!(res && (lvl < 2)) || !pte_valid(&pte));
    /* ...have enough space... */
    assert(!(res && (lvl < 2)) || (pt_lvlsize(&as->pt, lvl) <= (left * PAGE_SIZE)));
    /* ...and be correctly aligned */
    assert(!(res && (lvl < 2)) || ((vaddr % pt_lvlsize(&as->pt, lvl)) == 0));

    assert(proof_as_is_valid(as));
}
