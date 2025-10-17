// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file pt_get_pte_harness.c
 * @brief Implements the proof harness for pt_get_pte function.
 */

#include <assert.h>
#include <pt_helpers.h>
#include <addr_helpers.h>

/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    struct page_table *pt;
    pt = proof_pt_allocate();
    proof_pt_init(pt);
    proof_pt_fill(pt, 2);
    assert(proof_pt_is_valid(pt));

    size_t lvl;
    __CPROVER_assume(lvl < 3);
    vaddr_t vaddr;
    __CPROVER_assume(proof_vaddr_is_valid(vaddr));
    pte_t *res;

    res = pt_get_pte(pt, lvl, vaddr);
    assert(proof_pt_is_valid(pt));
}
