// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file mem_alloc_ppages_harness.c
 * @brief Implements the proof harness for mem_alloc_ppages function.
 */

#include <assert.h>
#include <mem.h>
#include <ppl_helpers.h>
#include <addr_helpers.h>

/* Stubs */
void spin_lock(spinlock_t* lock) { }
void spin_unlock(spinlock_t* lock) { }

bool pp_alloc(struct page_pool* pool, size_t num_pages, bool aligned,
              struct ppages* ppages)
{
    bool res;
    return res;
}

bool pp_alloc_clr(struct page_pool* pool, size_t num_pages, colormap_t colors,
                  struct ppages* ppages)
{
    bool res;
    return res;
}

/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    struct page_pool *pool = proof_ppl_init();
    colormap_t colors = 0;  /* we do not test coloring */
    size_t num_pages;
    __CPROVER_assume(num_pages < PROOF_PADDR_SIZE / PAGE_SIZE);
    bool phys_aligned;
    __CPROVER_assume(phys_aligned == true);
    struct ppages ppages;

    ppages = mem_alloc_ppages(colors, num_pages, phys_aligned);
    assert((ppages.num_pages == 0) || (ppages.num_pages == num_pages));
}
