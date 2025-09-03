// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file list_push_harness.c
 * @brief Implements the proof harness for list_push function.
 */

#include "list.h"
#include <assert.h>

/* Stubs */
void spin_lock(spinlock_t* lock) { }
void spin_unlock(spinlock_t* lock) { }

/**
 * @brief Starting point for formal analysis
 * 
 */
void harness(void)
{
    struct list l;
    struct list *lp = &l;

    struct node {
        uint8_t *next;
        uint64_t value;
    };
    struct node n1, n2;

    list_init(lp);
    assert(list_empty(lp));

    list_push(lp, &n1);
    assert(!list_empty(lp));

    /* add a second element to ensure 100% coverage */
    list_push(lp, &n2);
    assert(!list_empty(lp));
}
