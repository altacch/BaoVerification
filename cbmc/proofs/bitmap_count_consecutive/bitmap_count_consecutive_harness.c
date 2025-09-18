// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file bitmap_count_consecutive_harness.c
 * @brief Implements the proof harness for bitmap_count_consecutive function.
 */

#include "bitmap.h"
#include <assert.h>

/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    bitmap_t map[MAP_LEN];
    size_t size;
    __CPROVER_assume(size < BITMAP_GRANULE_LEN * MAP_LEN);
    size_t start;
    __CPROVER_assume(start < BITMAP_GRANULE_LEN * MAP_LEN);
    size_t n;
    __CPROVER_assume(n < BITMAP_GRANULE_LEN * MAP_LEN);
    size_t res;

    res = bitmap_count_consecutive(map, size, start, n);

    /* Note: result is a count, not an index, so equality is also good here */
    assert(res <= BITMAP_GRANULE_LEN * MAP_LEN);
}
