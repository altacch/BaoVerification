// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT-0

/*
 * Insert copyright notice
 */

/**
 * @file list_init_harness.c
 * @brief Implements the proof harness for list_init function.
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

    list_init(lp);
    assert(list_empty(lp));
}
