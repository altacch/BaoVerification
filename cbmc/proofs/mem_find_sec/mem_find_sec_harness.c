// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file mem_find_sec_harness.c
 * @brief Implements the proof harness for mem_find_sec function.
 */

#include <assert.h>
#include <mem.h>
#include <page_table.h>
#include <as_helpers.h>

struct section {
    vaddr_t beg;
    vaddr_t end;
    bool shared;
    spinlock_t lock;
};

struct section* mem_find_sec(struct addr_space* as, vaddr_t va);

extern struct section hyp_secs[4];

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

    size_t lvl;
    __CPROVER_assume(lvl < 3);
    vaddr_t va;
    struct section *res;

    res = mem_find_sec(as, va);
    assert(res == NULL ||
           ((res != NULL) &&
            (va >= hyp_secs[0].beg && va <= hyp_secs[0].end) ||
            (va >= hyp_secs[1].beg && va <= hyp_secs[1].end) ||
            (va >= hyp_secs[2].beg && va <= hyp_secs[2].end) ||
            (va >= hyp_secs[3].beg && va <= hyp_secs[3].end)));
}
