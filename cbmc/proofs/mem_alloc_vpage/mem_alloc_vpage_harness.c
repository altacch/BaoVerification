// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file mem_alloc_vpage_harness.c
 * @brief Implements the proof harness for mem_alloc_vpage function.
 */

#include <assert.h>
#include <mem.h>
#include <as_helpers.h>
#include <addr_helpers.h>

struct section {
    vaddr_t beg;
    vaddr_t end;
    bool shared;
    spinlock_t lock;
};

extern struct section hyp_secs[4];

/* Stubs */
void spin_lock(spinlock_t* lock) { }
void spin_unlock(spinlock_t* lock) { }
void console_printk(const char* fmt, ...) { }
void fence_sync_write(void) { }

struct section* mem_find_sec(struct addr_space* as, vaddr_t va)
{
    size_t idx;
    __CPROVER_assume(idx < 4);
    return &hyp_secs[idx];
}

pte_t* mem_alloc_pt(struct addr_space* as, pte_t* parent, size_t lvl, vaddr_t addr)
{
    /* to be improved */
    size_t i;
    __CPROVER_assume(i < ROOT_SIZE);    
    return &as->pt.root[i];
}


/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    struct addr_space* as;
    as = proof_as_allocate();
    proof_as_init(as);
    //    proof_pt_fill(&as->pt, 4);
    assert(proof_as_is_valid(as));

    // we only deal with the hypervisor address space for now
    enum AS_SEC section;
    __CPROVER_assume(section == SEC_HYP_GLOBAL ||
                     section == SEC_HYP_IMAGE ||
                     section == SEC_HYP_PRIVATE ||
                     section == SEC_HYP_VM);

    {
        /* Case 1: vaddr == INVALID_VA
           allocate at first free block of section */
        vaddr_t vaddr = INVALID_VA;
        size_t n;
        //__CPROVER_assume(n != 0);
        __CPROVER_assume(n <= MAX_N);
        vaddr_t res;

        res = mem_alloc_vpage(as, section, vaddr, n);
        //assert();
    }

    {
        /* Case 2: vaddr != INVALID_VA
           allocate at specified address */

        vaddr_t vaddr;
        __CPROVER_assume(proof_vaddr_is_valid(vaddr));
        __CPROVER_assume(vaddr != INVALID_VA);
        size_t n;
        //__CPROVER_assume(n != 0);
        __CPROVER_assume(n <= MAX_N);
        vaddr_t res;

        res = mem_alloc_vpage(as, section, vaddr, n);
        assert(res == INVALID_VA || proof_vaddr_is_valid(res));
    }

}
