// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file pp_alloc_harness.c
 * @brief Implements the proof harness for pp_alloc function.
 */

#include <assert.h>
#include <mem.h>
#include <ppl_helpers.h>
#include <addr_helpers.h>

/* Stubs */
void spin_lock(spinlock_t* lock) { }
void spin_unlock(spinlock_t* lock) { }

ssize_t bitmap_find_consec(bitmap_t* map, size_t size, size_t start, size_t n, bool set)
{
    ssize_t res;
    __CPROVER_assume((res == -1) || (res >= 0 && (size_t) res <= size)); // to be revised?
    return res;
}

void bitmap_set_consecutive(bitmap_t* map, size_t start, size_t n) { }

/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    struct page_pool *pool = proof_ppl_init();
    assert(proof_ppl_is_valid(pool));
    size_t num_pages;
    __CPROVER_assume(num_pages < PROOF_PADDR_SIZE / PAGE_SIZE);
    bool aligned;
    __CPROVER_assume(aligned == false);
    struct ppages ppages;  /* out parameter, no assumptions needed */
    bool res;

    res = pp_alloc(pool, num_pages, aligned, &ppages);
    assert(proof_ppl_is_valid(pool));
}
