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

/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    /* BIT32_MASK contract: 0 <= OFF < 32, 0 < LEN <= 32, OFF + LEN <= 32 */

    assert(BIT32_MASK(0,1) == 1U);
    assert(BIT32_MASK(0,31) == 2147483647U);
    assert(BIT32_MASK(0,32) == 4294967295U);
    assert(BIT32_MASK(1,1) == 2U);
    //assert(BIT32_MASK(1,31) == );
    assert(BIT32_MASK(2,1) == 4U);
    //assert(BIT32_MASK(2,30) == );
    //assert(BIT32_MASK(31,1) == );

    /* BIT64_MASK contract: 0 <= OFF < 64, 0 < LEN <= 64, OFF + LEN <= 64 */

    assert(BIT64_MASK(0,1) == 1UL);
    assert(BIT64_MASK(0,63) == 9223372036854775807UL);
    assert(BIT64_MASK(0,64) == 18446744073709551615UL);
    assert(BIT64_MASK(1,1) == 2UL);
    //    assert(BIT64_MASK(1,63) == );
    assert(BIT64_MASK(2,1) == 4U);
    // assert(BIT64_MASK(2,62) == );
    // assert(BIT64_MASK(61,1) == );

    assert(bit32_get(1U, 0U) == 1U);
    
    /* todo:
       bit32_get, bit32_set, bit32_clear, bit32_extract, bit32_insert,
       bit32_ffs, bit32_count
       bit64_get, bit64_set, bit64_clear, bit64_extract, bit64_insert,
       bit64_ffs, bit64_count
       bit_get, bit_set, bit_clear, bit_extract, bit_insert,
       bit_ffs, bit_count
    */

    // TODO: find a way to express correctness in terms of the internal
    // model checker primitives
}
