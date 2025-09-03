// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file memcpy_harness.c
 * @brief Implements the proof harness for memcpy function.
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

    uint8_t *a;     /* source array */
    uint8_t *b;     /* destination array */
    uint8_t *res;

    a = malloc(size);
    __CPROVER_assume(a != NULL);
    b = malloc(size);
    __CPROVER_assume(b != NULL);
    
    res = memcpy(b, a, size);

    /**
       Correctness specification for memcpy:
       forall size . forall 0 <= i < size . b[i] = a[i]
    */
    for (size_t i = 0; i < size; i++) {
        assert(a[i] == b[i]);
    }
    
    /** Return value is a pointer to the destination area */
    assert(res == b);

}
