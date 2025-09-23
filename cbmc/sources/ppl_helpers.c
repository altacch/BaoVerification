#include <addr_helpers.h>
#include <ppl_helpers.h>
#include <stdlib.h>
#include <string.h>

/* Init routine for page pool list (defined in src/core/mem.c) */
struct page_pool *proof_ppl_init(void)
{
    paddr_t root_region_base;
    __CPROVER_assume(root_region_base < PROOF_PADDR_SIZE - PAGE_SIZE);
    size_t root_region_size;
    __CPROVER_assume(root_region_size < PROOF_PADDR_SIZE);
    __CPROVER_assume(root_region_base + root_region_size < PROOF_PADDR_SIZE);
    
    /* taken from pp_root_init */
    root_pool.base = ALIGN(root_region_base, PAGE_SIZE);
    root_pool.num_pages = root_region_size / PAGE_SIZE;
    root_pool.free = root_pool.num_pages;
    root_pool.last = 0;

    /* Allocate and initialize bitmap */
    size_t bitmap_size = root_pool.num_pages / 8 + ((root_pool.num_pages % 8 != 0) ? 1 : 0);
    //size_t bitmap_num_pages = NUM_PAGES(bitmap_size);
    root_pool.bitmap = malloc(bitmap_size);
    __CPROVER_assume(root_pool.bitmap != NULL);
    memset(root_pool.bitmap, 0, bitmap_size);

    /* taken from mem_init */
    list_init(&page_pool_list);
    list_push(&page_pool_list, &(root_pool.node));

    return &root_pool;
}

bool proof_ppl_is_valid(struct page_pool *pp)
{
    if (pp == NULL) return false;
    if (!proof_paddr_is_valid(pp->base)) return false;
    if (pp->num_pages * PAGE_SIZE > PROOF_PADDR_SIZE) return false;
    if (pp->free > pp->num_pages) return false;
    if (pp->last > pp->num_pages) return false;
    if (root_pool.bitmap == NULL) return false;

    return true;
}
