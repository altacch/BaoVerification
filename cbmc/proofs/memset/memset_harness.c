// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file memset_harness.c
 * @brief Implements the proof harness for memset function.
 */

#include "string.h"
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    static const size_t size;
    __CPROVER_assume(size < ARRAY_SIZE);

    uint8_t *a;
    int val;
    uint8_t *res;

    a = malloc(size);
    __CPROVER_assume(a != NULL);

    res = memset(a, val, size);

    /**
       Correctness specification for memset:
       forall val, size . forall 0 <= i < size . a[i] = val & 255
    */
    for (size_t i = 0; i < size; i++) {
        assert(a[i] == (val & 255));
    }

    /** Return value is a pointer to the filled memory area */
    assert(res == a);

}
