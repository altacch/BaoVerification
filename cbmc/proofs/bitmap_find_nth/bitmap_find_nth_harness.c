// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file bitmap_find_nth_harness.c
 * @brief Implements the proof harness for bitmap_find_nth function.
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
    size_t nth;
    size_t start;
    bool set;
    ssize_t res;

    __CPROVER_assume(size < BITMAP_GRANULE_LEN * MAP_LEN);
    __CPROVER_assume(nth < BITMAP_GRANULE_LEN * MAP_LEN);
    __CPROVER_assume(start < BITMAP_GRANULE_LEN * MAP_LEN);

    res = bitmap_find_nth(map, size, nth, start, set);

    assert((res == -1) || ((res >= 0) && (res < BITMAP_GRANULE_LEN * MAP_LEN)));
}
