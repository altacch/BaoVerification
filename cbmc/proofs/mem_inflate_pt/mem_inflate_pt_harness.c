// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file mem_inflate_pt_harness.c
 * @brief Implements the proof harness for mem_inflate_pt function.
 */

#include <assert.h>
#include <mem.h>
#include <arch/sbi.h>
#include <as_helpers.h>

void mem_inflate_pt(struct addr_space* as, vaddr_t va, size_t length);

/* Stubs */
void mem_expand_pte(struct addr_space* as, vaddr_t va, size_t lvl) { }

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

    vaddr_t addr;
    __CPROVER_assume(proof_vaddr_is_valid(addr));
    size_t length;
    __CPROVER_assume(length < ROOT_SIZE);

    mem_inflate_pt(as, addr, length);
    assert(proof_as_is_valid(as));
}
