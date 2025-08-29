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

/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{

    /* Insert argument declarations */
    uint8_t a[ARRAY_SIZE] = { 42 };  /* source array */
    uint8_t b[ARRAY_SIZE];           /* destination array */
    uint8_t *res;

    res = memcpy(b, a, ARRAY_SIZE);

    /**
       Correctness specification for memcpy:
       forall size . forall 0 <= i < size . b[i] = a[i]
    */
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        assert(a[i] == b[i]);
    }
    
    /** Return value is a pointer to the destination area */
    assert(res == &b);
    
}
