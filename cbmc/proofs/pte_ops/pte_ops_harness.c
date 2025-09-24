// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file pte_ops_harness.c
 * @brief Implements the proof harness for risc-v specific pte_* functions.
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
    
    /* Verification of pte_set, pte_valid, pte_addr
       Contract: after pte_set has been called, the PTE is valid and
       its address coincides with the upper part of addr */
    {
        pte_t current_pte = pt->root[i];
        paddr_t addr;
        pte_type_t type;
        pte_flags_t flags;

        pte_set(&current_pte, addr, type, flags);

        /* Check validity */
        if (flags & PTE_VALID) {
            assert(pte_valid(&current_pte));
        }
        
        /* Check address has been stored */
        assert(pte_addr(&current_pte) == (addr & PTE_ADDR_MSK));

        /* Check flags have been stored (how?) */
    }

    /* Verification of pte_set_rsw, pte_check_rsw */
    {
        pte_t current_pte = pt->root[i];
        pte_flags_t flags;

        pte_set_rsw(&current_pte, flags);
        assert(pte_check_rsw(&current_pte, flags));
    }

    /* Verification of pte_table */
    {
        pte_t current_pte = pt->root[i];
        size_t lvl;
        __CPROVER_assume(lvl < 3);
        bool result = pte_table(pt, &current_pte, lvl);
        bool expected = pte_valid(&current_pte) && ((current_pte & PTE_RWX) == 0);
        assert(result == expected);
    }

}
