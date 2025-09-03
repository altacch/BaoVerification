// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file list_rm_harness.c
 * @brief Implements the proof harness for list_rm function.
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
    struct node n1, n2, n3;
    bool res;

    list_init(lp);

    list_push(lp, &n1);
    assert(!list_empty(lp));

    /* test 1: node not present */
    res = list_rm(lp, &n2);
    //    assert(res == false);

    /* test 2: remove first node in 1-element list */
    res = list_rm(lp, &n1);
    assert(res == true);
    assert(list_empty(lp));

    /* test 3: remove first node in 2-element list */
    list_push(lp, &n1);
    list_push(lp, &n2);
    res = list_rm(lp, &n2);
    assert(res == true);
    assert(!list_empty(lp));

    /* test 3: remove second node in 3-element list */
    list_push(lp, &n1);
    list_push(lp, &n2);
    list_push(lp, &n3);
    res = list_rm(lp, &n2);
    assert(res == true);
    assert(!list_empty(lp));
}
