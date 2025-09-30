// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file mem_expand_pte_harness.c
 * @brief Implements the proof harness for mem_expand_pte function.
 */

#include <assert.h>
#include <stdlib.h>
#include <mem.h>
#include <arch/sbi.h>
#include <as_helpers.h>

void mem_expand_pte(struct addr_space* as, vaddr_t va, size_t lvl);

/* Stubs */
void fence_sync_write(void) { }
void tlb_inv_va(struct addr_space* as, vaddr_t va) { }

/*pte_t* pt_get(struct page_table* pt, size_t lvl, vaddr_t va)
{
    size_t pte_index;
    __CPROVER_assume(pte_index < ROOT_SIZE);
    pte_t* pte = pt->root[pte_index];
    return pte;
    }*/

pte_t* mem_alloc_pt(struct addr_space* as, pte_t* parent, size_t lvl, vaddr_t addr)
{
    // never fails
    pte_t *res = malloc(ROOT_SIZE * sizeof(pte_t));
    __CPROVER_assume(res != NULL);
    return res;
}

/*
struct sbiret sbi_remote_sfence_vma(const unsigned long hart_mask, unsigned long hart_mask_base,
                                    unsigned long start_addr, unsigned long size)
{
    struct sbiret res;
    // introduce assumptions here
    return res;
}
struct sbiret sbi_remote_hfence_gvma_vmid(const unsigned long hart_mask, unsigned long hart_mask_base, unsigned long start_addr, unsigned long size, unsigned long vmid)
{
    struct sbiret res;
    // introduce assumptions here
    return res;
}
*/

/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    struct addr_space* as;
    as = proof_as_allocate();
    proof_hier_as_init(as);
    assert(proof_hier_as_is_valid(as));

    /*bool ok;
      alloc_successful = ok;*/

    vaddr_t addr;
    __CPROVER_assume(proof_vaddr_is_valid(addr));
    size_t lvl;
    __CPROVER_assume(lvl < 3);

    mem_expand_pte(as, addr, lvl);
    assert(proof_hier_as_is_valid(as));
}
