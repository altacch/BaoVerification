// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file bit_harness.c
 * @brief Implements the proof harness for bit function.
 */

#include "bit.h"
#include <assert.h>

ssize_t my_ffs(uint64_t word)
{
    if (word == 0) return (ssize_t) ~0L;
    ssize_t pos = 0;
    if ((word & 0xFFFFFFFF) == 0) {
        pos += 32;
        word >>= 32;
    }
    if ((word & 0xFFFF) == 0) {
        pos += 16;
        word >>= 16;
    }
    if ((word & 0xFF) == 0) {
        pos += 8;
        word >>= 8;
    }
    if ((word & 0xF) == 0) {
        pos += 4;
        word >>= 4;
    }
    if ((word & 0x3) == 0) {
        pos += 2;
        word >>=  2;
    }
    if ((word & 0x1) == 0) {
        return pos+1;
    } else {
        return pos;
    }
}

size_t my_popcnt(uint64_t word)
/* using Wegner algorithm, uniform in word size */
{
    size_t count = 0;
    for (; word != 0; count++) {
        word &= word - 1;
    }
    return count;
}    

/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    /* BIT32_MASK contract: 0 <= OFF < 32 */

    assert(BIT32_MASK(0,0)  == 0x00000000U);
    assert(BIT32_MASK(0,1)  == 0x00000001U);
    assert(BIT32_MASK(0,31) == 0x7FFFFFFFU);
    assert(BIT32_MASK(0,32) == 0xFFFFFFFFU);
    assert(BIT32_MASK(1,0)  == 0x00000000U);
    assert(BIT32_MASK(1,1)  == 0x00000002U);
    assert(BIT32_MASK(1,31) == 0xFFFFFFFEU);
    assert(BIT32_MASK(2,0)  == 0x00000000U);
    assert(BIT32_MASK(2,1)  == 0x00000004U);
    assert(BIT32_MASK(2,30) == 0xFFFFFFFCU);
    assert(BIT32_MASK(31,0) == 0x00000000U);
    assert(BIT32_MASK(31,1) == 0x80000000U);

    /* BIT64_MASK contract: 0 <= OFF < 64 */

    assert(BIT64_MASK(0,0)  == 0x0000000000000000U);
    assert(BIT64_MASK(0,1)  == 0x0000000000000001U);
    assert(BIT64_MASK(0,63) == 0x7FFFFFFFFFFFFFFFU);
    assert(BIT64_MASK(0,64) == 0xFFFFFFFFFFFFFFFFU);
    assert(BIT64_MASK(1,0)  == 0x0000000000000000U);
    assert(BIT64_MASK(1,1)  == 0x0000000000000002U);
    assert(BIT64_MASK(1,63) == 0xFFFFFFFFFFFFFFFEU);
    assert(BIT64_MASK(2,0)  == 0x0000000000000000U);
    assert(BIT64_MASK(2,1)  == 0x0000000000000004U);
    assert(BIT64_MASK(2,62) == 0xFFFFFFFFFFFFFFFCU);
    assert(BIT64_MASK(63,0) == 0x0000000000000000U);
    assert(BIT64_MASK(63,1) == 0x8000000000000000U);

    /* Verification of bit32_get */
    {
        uint32_t word;
        size_t off;
        __CPROVER_assume(off < 32);
        assert(bit32_get(word,off) == (word & BIT32_MASK(off,1)));
    }

    /* Verification of bit32_set */
    {
        uint32_t word;
        size_t off;
        __CPROVER_assume(off < 32);
        assert(bit32_set(word,off) == (word | BIT32_MASK(off,1)));
    }

    /* Verification of bit32_clear */
    {
        uint32_t word;
        size_t off;
        __CPROVER_assume(off < 32);
        assert(bit32_clear(word,off) == (word & ~(BIT32_MASK(off,1))));
    }

    /* Verification of bit32_extract */
    {
        uint32_t word;
        size_t off;
        __CPROVER_assume(off < 32);
        size_t len;
        __CPROVER_assume(len <= 32);
        assert(bit32_extract(word,off,len) == ((word & BIT32_MASK(off,len)) >> off));
    }
    
    /* Verification of bit32_insert */
    {
        uint32_t word;
        uint32_t val;
        size_t off;
        __CPROVER_assume(off < 32);
        size_t len;
        __CPROVER_assume(len <= 32);
        uint32_t res = bit32_insert(word,val,off,len);
        assert((res & ~(BIT32_MASK(off,len))) == (word & ~(BIT32_MASK(off,len))));
        assert((res & BIT32_MASK(off,len)) == ((val & BIT32_MASK(0,len)) << off));
    }

    /* Verification of bit32_ffs */
    {
        uint32_t word;
        assert(bit32_ffs(word) == my_ffs(word));
    }

    /* Verification of bit32_count */
    {
        uint32_t word;
        assert(bit32_count(word) == my_popcnt(word));
    }

    /* Verification of bit64_get */
    {
        uint64_t word;
        size_t off;
        __CPROVER_assume(off < 64);
        assert(bit64_get(word,off) == (word & BIT64_MASK(off,1)));
    }

    /* Verification of bit64_set */
    {
        uint64_t word;
        size_t off;
        __CPROVER_assume(off < 64);
        assert(bit64_set(word,off) == (word | BIT64_MASK(off,1)));
    }

    /* Verification of bit64_clear */
    {
        uint64_t word;
        size_t off;
        __CPROVER_assume(off < 64);
        assert(bit64_clear(word,off) == (word & ~(BIT64_MASK(off,1))));
    }

    /* Verification of bit64_extract */
    {
        uint64_t word;
        size_t off;
        __CPROVER_assume(off < 64);
        size_t len;
        __CPROVER_assume(len <= 64);
        assert(bit64_extract(word,off,len) == ((word & BIT64_MASK(off,len)) >> off));
    }
    
    /* Verification of bit64_insert */
    {
        uint64_t word;
        uint64_t val;
        size_t off;
        __CPROVER_assume(off < 64);
        size_t len;
        __CPROVER_assume(len <= 64);
        uint64_t res = bit64_insert(word,val,off,len);
        assert((res & ~(BIT64_MASK(off,len))) == (word & ~(BIT64_MASK(off,len))));
        assert((res & BIT64_MASK(off,len)) == ((val & BIT64_MASK(0,len)) << off));
    }

    /* Verification of bit64_ffs */
    {
        uint64_t word;
        assert(bit64_ffs(word) == my_ffs(word));
    }

    /* Verification of bit64_count */
    {
        uint64_t word;
        assert(bit64_count(word) == my_popcnt(word));
    }

    // TODO: find a way to express correctness in terms of the internal
    // model checker primitives
}
