// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file list_peek_harness.c
 * @brief Implements the proof harness for list_peek function.
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
    struct node n1;
    uint64_t val;
    struct node *res;
    
    n1.value = val;
    
    list_init(lp);

    list_push(lp, &n1);

    res = (struct node *) list_peek(lp);
    assert(res != NULL);
    assert(res->next == NULL);
    assert(res->value == val);
    assert(!list_empty(lp));
}
