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

/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    /* Argument declarations */
    uint8_t a[ARRAY_SIZE];
    int val;
    uint8_t *res;

    res = (uint8_t *) memset(a, val, ARRAY_SIZE);

    /**
       Correctness specification for memset:
       forall val, size . forall 0 <= i < size . a[i] = val & 255
    */
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        assert(a[i] == (val & 255));
    }

    /** Return value is a pointer to the filled memory area */
    assert(res == &a);

}
