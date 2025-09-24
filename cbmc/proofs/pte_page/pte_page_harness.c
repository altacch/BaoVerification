// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file pte_page_harness.c
 * @brief Implements the proof harness for pte_page function.
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

    size_t i;
    __CPROVER_assume(i < ROOT_SIZE);
    pte_t pte = pt->root[i];
    size_t lvl;
    __CPROVER_assume(lvl < 3);
    bool res;

    res = pte_page(pt, &pte, lvl);
    /* A PTE for a subtable must be valid */
    assert(!res || pte_valid(&pte));
    assert(!res || ((pte & PTE_RWX) != 0));
}
