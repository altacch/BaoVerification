// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file bitmap_find_consec_harness.c
 * @brief Implements the proof harness for bitmap_find_consec function.
 */

#include "bitmap.h"
#include <assert.h>

/* Stubs */
ssize_t bitmap_find_nth(bitmap_t* map, size_t size, size_t nth, size_t start, bool set)
{
    assert(size < BITMAP_GRANULE_LEN * MAP_LEN);
    assert(nth < BITMAP_GRANULE_LEN * MAP_LEN);
    ssize_t res;
    __CPROVER_assume((start < BITMAP_GRANULE_LEN * MAP_LEN) || (res == -1));
    __CPROVER_assume((res == -1) || ((res >= 0) && (res < BITMAP_GRANULE_LEN * MAP_LEN)));
    return res;
}

size_t bitmap_count_consecutive(bitmap_t* map, size_t size, size_t start, size_t n)
{
    assert(size < BITMAP_GRANULE_LEN * MAP_LEN);
    //assert(start < BITMAP_GRANULE_LEN * MAP_LEN);
    size_t res;
    __CPROVER_assume((start < BITMAP_GRANULE_LEN * MAP_LEN) || (res == 0));
    __CPROVER_assume(res <= BITMAP_GRANULE_LEN * MAP_LEN);
    return res;
}

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
    /* __CPROVER_assume(start < BITMAP_GRANULE_LEN * MAP_LEN); */
    size_t n;
    __CPROVER_assume(n < BITMAP_GRANULE_LEN * MAP_LEN);
    bool set;
    ssize_t res;

    res = bitmap_find_consec(map, size, start, n, set);
    /* if start is out of bounds, return -1 */
    assert((start < BITMAP_GRANULE_LEN * MAP_LEN) || (res == -1));
    /* in any case, return either -1 or a valid result */
    assert((res == -1) || ((res >= 0) && (res < BITMAP_GRANULE_LEN * MAP_LEN)));
}
