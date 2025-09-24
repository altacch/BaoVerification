// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file pt_ops_harness.c
 * @brief Implements the proof harness for inlined pt_* functions (RISC-V version).
 */

#include <assert.h>
#include <pt_helpers.h>
#include <page_table.h>

/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    struct page_table *pt;
    pt = proof_pt_allocate();
    proof_pt_init(pt);
    assert(proof_pt_is_valid(pt));

    size_t lvl;
    __CPROVER_assume(lvl < 3);
    size_t res;

    /* Verification of pt_nentries */
    res = pt_nentries(pt, lvl);
    assert(res == 512);

    /* Verification of pt_lvlsize */
    res = pt_lvlsize(pt, lvl);
    assert((lvl == 0 && res == 1073741824U) ||
           (lvl == 1 && res == 2097152U) ||
           (lvl == 2 && res == 4096U));

    /* Verification of pt_size */
    res = pt_size(pt, lvl);
    assert(res == 4096U);

    /* Verification of pt_getpteindex */
    size_t i;
    __CPROVER_assume(i < ROOT_SIZE);
    pte_t current_pte = pt->root[i];
    res = pt_getpteindex(pt, &current_pte, lvl);
    assert(res == (((uintptr_t) &current_pte) & 4095U) / 8);

    /* Verification of pt_getpteindex_by_va */
    vaddr_t va;
    res = pt_getpteindex_by_va(pt, va, lvl);
    assert(res < 512U);

    /* Verification of pt_lvlterminal */
    assert(pt_lvl_terminal(pt, lvl) == true);
}
